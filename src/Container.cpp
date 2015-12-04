#include "Container.hpp"
#include "Trigger.hpp"
#include "Zork_Def.hpp"
#include "Map.hpp"

using namespace std;

Container::Container(const string& n,const string& desc, const string& status):
Object(n,desc,status)
{
	Trigger trig = Trigger(NULL,name+" is locked",true);
	trig.addCondition([this](){
		return this->status=="locked";
	});
	addTrigger(trig);

	trig = Trigger(NULL,name+" is opened",true);
	trig.addCondition([this](){
		return (this->status!="locked");
	});
	trig.addAction([this](const string& s){
		if(this->item.size()==0){
			cout<<"It is empty!"<<endl;
			return;
		}
		cout<<"It contains:"<<endl;
		list<reference_wrapper<Item> >::iterator i;
		for(i=item.begin();i!=item.end();++i){
			Object& tmp = *i;
			cout<<tmp.getname()<<endl;
			getowner().Add(tmp);
		}
	});
	addTrigger(trig);
}

void Container::Add(Object& c)
{
	list<reference_wrapper<Item> >::iterator i;
	if(c.getowner()!=ZorkMap.getInventory()){
		cout<<"You do not have this item."<<endl;
		return;
	}
	for(i=accept.begin();i!=accept.end();++i){
		if(c==(*i)) break;
	}
	if(i==accept.end()){
		cout<<"You cannot put in this item"<<endl;
		return;
	}
	reference_wrapper<Item> wp = ref(static_cast<Item&>(c));
	item.push_front(wp);
	c.Belong(*this);
}

void Container::Delete()
{
	list<reference_wrapper<Item> >::iterator i;
	for(i=item.begin();i!=item.end();++i){
		Object& obj = *i;
		getowner().Add(obj);
		obj.Belong(getowner());
	}
}

void Container::Remove(Object& c)
{
	if(!Has(c)) return;
	reference_wrapper<Object> wp = ref(c);
	c.Belong(wp);
	list<reference_wrapper<Item> >::iterator i;
	for(i=item.begin();i!=item.end();++i){
		if(c==(*i)) break;
	}
	item.erase(i);
}
