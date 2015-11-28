#ifndef _ZORK_OBJECT_
#define _ZORK_OBJECT_

#include <string>
#include "Trigger.hpp"
#include <list>
#include <functional>

using namespace std;

class Object;

typedef reference_wrapper<Object> ObjRef;

class Object
{
public:

	Object(string& n,string& desc,string&status):
	name(n),descrip(desc),status(status),check(false);

	const string& getname() const{return name;}
	const string& getstatus() const{return status;}
	const string& getdescrip const{return descrip;}

	void addTrigger(Trigger trig){tri.push_back(trig);}
	void addBelong(ObjRef c){belong.push_back(c)};

	bool isBelong(ObjRef c)
	{
		list<ObjRef>::iterator i;
		for(i=belong.begin();i!=belong.end();i++){
			if(*i==c) return true;
		}
		return false;
	}

	void React()
	{
		list<Trigger>::iterator i;
		check = true;
		while(check){
			check = false;
			for(i=tri.begin();i!=tri.end();++i){
				if(i->getCMD()) continue;
				check &= i->run();
				if(!i->isPerm()){
					tri.erase(i--);
				}
			}
		}
	}

	void React(string& cmd)
	{
		list<Trigger>::iterator i;
		check = false;
		for(i=tri.begin();i!=tri.end();++i){
			if((i->getCMD())!=cmd) continue;
			check &= i->run();
			if(!i->isPerm()){
				tri.erase(i--);
			}
		}
		if(check)React();
	}

	virtual void Add(Object &c);
	virtual void Delete()
	{
		list<ObjRef>::iterator i;
		for(i=belong.begin();i!=belong.end();++i){
			i->RemoveFrom(*this);
		}
	}
	virtual void RemoveFrom(ObjRef c);
	virtual void Update(string newstatus)
	{
		status = newstatus;
	}
	virtual bool Has(Object& c)
	{return false;}
private:
	string name;
	string descrip;
	string status;
	list<ObjRef> belong;// contained by Container or Room
	list<Trigger> tri;
	bool check;
}

#endif
