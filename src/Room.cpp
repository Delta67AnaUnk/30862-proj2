#include "Room.hpp"
#include "Trigger.hpp"
#include "Zork_Def.hpp"
#include "Map.hpp"

using namespace std;


Room::Room(const string& n,const string& desc,const string& status, const string& type):
Object(n,desc,status),type(type)
{
	int i;
	Trigger trig("","",false);
	const string dirs[4] = {"n","e","s","w"};
	for(i=0;i<4;i++){
		// Set borders to null
		addBorder(emptystr,i);
		
		// Triggers for move
		trig = Trigger(dirs[i],"Can't go there",true);
		trig.addCondition([this,i]()->bool{
			return this->border[i].empty()==true;
		});
		addTrigger(trig);
	
		trig = Trigger(dirs[i],"",true);
		trig.addCondition([this,i]()->bool{
			return this->border[i].empty()==false;
		});
		trig.addAction([this,i](const string& s){
			ZorkMap.getCurrentRoom() = (static_cast<Room&>(ZorkMap.get(border[i])));
			cout<<ZorkMap.getCurrentRoom().getname()<<endl;
			cout<<ZorkMap.getCurrentRoom().getdescrip()<<endl;
		});
		addTrigger(trig);
	}
}

void Room::Add(Object& c)
{
	if(c.getowner()!=Inventory){
		cout<<"You do not have this item."<<endl;
		return;
	}
	if(string("Container")==typeid(c).name()){
		reference_wrapper<Container> wp = ref(static_cast<Container&>(c));
		cont.push_front(wp);
	}else if(string("Item")==typeid(c).name()){
		reference_wrapper<Item> wp = ref(static_cast<Item&>(c));
		item.push_front(wp);
	}else if(string("Creature")==typeid(c).name()){
		reference_wrapper<Creature> wp = ref(static_cast<Creature&>(c));
		being.push_front(wp);
	}
	c.Belong(*this);
}

void Room::Delete()
{
	int i = 0;
	for(i = 0;i<4;i++){
		if(!border[i].empty()){
			Room& rm = (Room&)ZorkMap.get(border[i]);
			rm.removeBorder((i+2)%4);
		}
	}
}

void Room::Remove(Object& c)
{
	if(!Has(c)) return;
	if(string("Container")==typeid(c).name()){
		decltype(cont)::iterator i;
		for(i=cont.begin();i!=cont.end();++i){
			if(c==*i) break;
		}
		cont.erase(i);
	}else if(string("Item")==typeid(c).name()){
		decltype(item)::iterator i;
		for(i=item.begin();i!=item.end();++i){
			if(c==*i) break;
		}
		item.erase(i);
	}else if(string("Creature")==typeid(c).name()){
		decltype(being)::iterator i;
		for(i=being.begin();i!=being.end();++i){
			if(c==*i) break;
		}
		being.erase(i);
	}
	c.RemoveFrom();
}
