#include "Item.hpp"
#include "Map.hpp"

using namespace std;

Item::Item(const string& name, const string& desc, const string& status,bool enable):
Object(name,desc,status),turnon(enable)
{
	// Trigger for drop
	Trigger drop = Trigger("drop",name+" is dropped",true);
	drop.addCondition([this](){
		return getowner()==ZorkMap.getInventory();
	});
	drop.addAction([this](const string& s){
		ZorkMap.getInventory().Remove(*this);
		ZorkMap.getCurrentRoom().Add(*this);
	});
	addTrigger(drop);

	// Trigger for put
	Trigger put = Trigger("put",name+" is put",true);
	put.addCondition([this](){
		return getowner()==ZorkMap.getInventory();
	});
	put.addAction([this](const string& s){
		vector<string>s2 = WordParser(s);
		if(s2.size()<4){
			cout<<"Not enough arguments"<<endl;
			return;
		}
		ZorkMap.getInventory().Remove(*this);
		if(string("Container")!=typeid(ZorkMap.get(s2[3])).name()){
			cout<<"Not a container"<<endl;
			return;
		}
		ZorkMap.get(s2[3]).Add(*this);
	});
	addTrigger(put);
}

void Item::addTurnon(string& prt,
	list<Action>::iterator s1,
	list<Action>::iterator e1)

{
	if(!turnon){ // cannot turnon
		Trigger trig = Trigger("turn on "+name,"Not applicable for this item",true);
		addTrigger(trig);
	}else{
		Trigger trig = Trigger("turn on "+name,prt,false);
		list<Action>::iterator i;
		for(i=s1;i!=e1;++i){
			trig.addAction(*i);
		}
		addTrigger(trig);
	}
}
