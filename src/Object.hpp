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

	Object(const string& n,const string& desc,const string&status):
	name(n),descrip(desc),status(status),check(false),belong(ref(*this)),handleid(maxhandle++){}

	bool operator== (const Object& comp)const
	{return handleid==comp.handleid;}

	bool operator!= (const Object& comp)const
	{return handleid!=comp.handleid;}

	const string& getname() const{return name;}
	const string& getstatus() const{return status;}
	const string& getdescrip() const{return descrip;}
	const Object& getowner() const{return belong;}
	Object& getowner() {return belong;}

	void addTrigger(Trigger trig){tri.push_front(trig);}
	void Belong(Object& c){belong=ref(c);};
	void RemoveFrom(){belong = ref(*this);}

	void React();

	void React(string& cmd);

	virtual void Add(Object& c);
	virtual void Delete(){belong = ref(*this);}
	virtual void Update(string newstatus)
	{status = newstatus;}

	virtual bool Has(const Object& c){return false;}
	virtual void Remove(Object& c);
protected:
	string name;
	string descrip;
	string status;
	ObjectRef belong;// contained by Container or Room
	list<Trigger> tri;
	list<Trigger>::iterator defaultEvents;
	bool check;
	int handleid;

	static int maxhandle;
};

static string emptystr;
Object NullObj(emptystr,emptystr,emptystr);

#endif
