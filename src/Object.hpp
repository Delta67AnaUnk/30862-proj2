#ifndef _ZORK_OBJECT_
#define _ZORK_OBJECT_

#include <string>
#include "Trigger.hpp"
#include <list>
#include <functional>

using namespace std;

class Object;

typedef reference_wrapper<Object> ObjectRef;

class Object
{
public:

	Object(string& n,string& desc,string&status):
	name(n),descrip(desc),status(status),check(false),handleid(maxhandle++);

	bool operator==(const Object& comp)
	{return handleid==comp.handleid;}

	const string& getname() const{return name;}
	const string& getstatus() const{return status;}
	const string& getdescrip() const{return descrip;}
	const Object& getowner() const{return belong;}

	void addTrigger(Trigger trig){tri.push_back(trig);}
	void Belong(Object& c){belong=ref(c);};
	void RemoveFrom(){belong = NULL;}

	void React();

	void React(string& cmd);

	virtual void Add(Object& c);
	virtual void Delete(){belong = NULL;}
	virtual void Update(string newstatus)
	{status = newstatus;}

	virtual bool Has(Object& c){return false;}
	virtual void Remove(Object& c);
protected:
	string name;
	string descrip;
	string status;
	ObjectRef belong;// contained by Container or Room
	list<Trigger> tri;
	bool check;
	int handleid;

	static int maxhandle = 0;
}

#endif
