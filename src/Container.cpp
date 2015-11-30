#include "Container.hpp"
#include "Trigger.hpp"
#include "Zork_Def.hpp"
#include "Zork_main.hpp"

using namespace std;

Container::Container(string& n,string& desc,string& status):
Object(n,desc,status)
{
	Trigger trig;
	trig = Trigger(NULL,name+" is locked",true);
	trig.addCondition([this](){
		return status=="locked";
	});
	addTrigger(trig);

	trig = Trigger(NULL,name+" is opened",true);
	trig.addCondition([this](){
		return (status!="locked");
	});
	trig.addAction([this](string& s){
		if(item.size()==0){
			cout<<"It is empty!"<<endl;
			return;
		}
		cout<<"It contains:"<<endl;
		list<reference_wrapper<Item> >::iterator i;
		for(i=item.begin();i!=item.end();++i){
			cout<<i->getname()<<endl;
			getowner().Add(*i);
		}
	});
	addTrigger(trig);
}

void Container::Add(Object& c)
{
	list<reference_wrapper<Item> >::iterator i;
	if(c.getowner()!=Inventory){
		cout<<"You do not have this item."<<endl;
		return;
	}
	for(i=accept.begin();i!=accept.end();++i){
		if(*i==c) break;
	}
	if(i==accept.end()){
		cout<<"You cannot put in this item"<<endl;
		return;
	}
	item.push_back(ref(c));
	c.Belong(*this);
}

void Container::Delete()
{
	list<reference_wrapper<Item> >::iterator i;
	for(i=item.begin();i!=item.end();++i){
		getowner().Add(*i);
		i->Belong(getowner());
	}
}

void Container::Remove(Object& c)
{
	if(!Has(c)) return;
	c.Belong(NULL);
	list<reference_wrapper<Item> >::iterator i;
	for(i=item.begin();i!=item.end();++i){
		if(*i==c) break;
	}
	item.erase(i);
}
