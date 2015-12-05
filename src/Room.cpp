#include "Room.hpp"
#include "Trigger.hpp"
#include "Zork_Def.hpp"
#include "Zork_main.hpp"

using namespace std;


Room::Room(string& n,string& desc,string& status, string& type):
Object(n,desc,status),type(type)
{
	int i;
	Trigger trig;
	const string dirs[4] = {"n","e","s","w"};
	for(i=0;i<4;i++){
		// Set borders to null
		addBorder(NULL,i);
		
		// Triggers for move
		trig = Trigger(dirs[i],"Can't go there",true);
		trig.addCondition([this](){
			return (border[i]==NULL);
		});
		addTrigger(trig);
	
		trig = Trigger(dirs[i],NULL,true);
		trig.addCondition([this](){
			return (border[i]!=NULL);
		});
		trig.addAction([this](string& s){
			CurRoomPtr = &(static_cast<Room>(ZorkMap.get(border[i])));
			cout<<CurRoomPtr.getname()<<endl;
			cout<<CurRoomPtr.getdescrip()<<endl;
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
		cont.push_front(ref(c));
	}else if(string("Item")==typeid(c).name()){
		item.push_front(ref(c));
	}else if(string("Creature")==typeid(c).name()){
		being.push_front(ref(c));
	}
	c.Belong(*this);
}

void Room::Delete()
{
	int i = 0;
	for(i = 0;i<4;i++){
		if(border[i]){
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
			if(*i==c) break;
		}
		cont.erase(i);
	}else if(string("Item")==typeid(c).name()){
		decltype(item)::iterator i;
		for(i=item.begin();i!=item.end();++i){
			if(*i==c) break;
		}
		item.erase(i);
	}else if(string("Creature")==typeid(c).name()){
		decltype(being)::iterator i;
		for(i=being.begin();i!=being.end();++i){
			if(*i==c) break;
		}
		being.erase(i);
	}
	c->RemoveFrom(*this);
}
