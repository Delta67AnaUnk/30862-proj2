#include "Room.hpp"
#include "Trigger.hpp"
#include "Zork_Def.hpp"
#include "Map.hpp"
#include "main.hpp"

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
		trig.addAction([this,i,ZorkMap](const string& s){
			ZorkMap->Move(border[i]);
		});
		addTrigger(trig);
	}
	defaultEvents = tri.begin();
}

void Room::Add(Item& c)
{
	if(c.getowner()!=ZorkMap->getInventory()){
		cout<<"You do not have this item."<<endl;
		return;
	}
	reference_wrapper<Item> wp = ref(c);
	item.push_front(wp);
	c.Belong(*this);
}

void Room::Add(Container& c)
{
	reference_wrapper<Container> wp = ref(c);
	cont.push_front(wp);
	c.Belong(*this);
}

void Room::Add(Creature& c)
{
	reference_wrapper<Creature> wp = ref(c);
	being.push_front(wp);
	c.Belong(*this);
}

void Room::Delete()
{
	int i = 0;
	for(i = 0;i<4;i++){
		if(!border[i].empty()){
			Room& rm = (Room&)ZorkMap->get(border[i]);
			rm.removeBorder((i+2)%4);
		}
	}
}

void Room::Remove(Item& c)
{
	if(!Has(c)) return;
	decltype(item)::iterator i;
	for(i=item.begin();i!=item.end();++i){
		if(c==i->get()) break;
	}
	item.erase(i);
	c.RemoveFrom();
}

void Room::Remove(Container& c)
{
	if(!Has(c)) return;
	decltype(cont)::iterator i;
	for(i=cont.begin();i!=cont.end();++i){
		if(c==i->get()) break;
	}
	cont.erase(i);
	c.RemoveFrom();
}

void Room::Remove(Creature& c)
{
	if(!Has(c)) return;
	decltype(being)::iterator i;
	for(i=being.begin();i!=being.end();++i){
		if(c==i->get()) break;
	}
	being.erase(i);
	c.RemoveFrom();
}
