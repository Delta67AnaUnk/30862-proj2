#include "Item.hpp"
#include "Zork_main.hpp"

using namespace std;

Item(string& n,string&desc, string& status,bool enable):
Object(n,desc,status),turnon(enable)
{
	// Trigger for drop
	Trigger drop = Trigger("drop",name+" is dropped",true);
	drop.addCondition([this](){
		return getowner()==Inventory;
	});
	drop.addAction([this](string& s){
		Inventory.Remove(*this);
		CurRoomPtr->Add(*this)
	});
	addTrigger(drop);

	// Trigger for put
	Trigger put = Trigger("put",name+" is put",true);
	put.addCondition([this](){
		return getowner()==Inventory;
	});
	put.addAction([this](string& s){
		list<string>s2 = WordParser(s);
		if(s2.size()<4){
			cout<<"Not enough arguments"<<endl;
			return;
		}
		Inventory.Remove(*this);
		if(string("Container")!=typeid(ZorkMap.get(s2[3])).name()){
			cout<<"Not a container"<<endl;
			return;
		}
		ZorkMap.get(s2[3]).Add(*this);
	});
	addTrigger(put);
}

void addTurnon(string& prt,
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
