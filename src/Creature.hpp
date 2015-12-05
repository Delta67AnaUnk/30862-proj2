#ifndef _ZORK_CREATURE_
#define _ZORK_CREATURE_

#include "Object.hpp"
#include <list>
#include <functional>
#include "Zork_Def.hpp" 

using namespace std;

class Creature:public Object
{
public:
	Creature(const string& n,const string& desc,const string& status):
	Object(n,desc,status){}

	void addVul(Object& vul){vulner.push_front(ref(vul));}

	void addAttack(string& prt,
	list<Condition>::iterator s1,
	list<Condition>::iterator e1,
	list<Action>::iterator s2,
	list<Action>::iterator e2);

private:
	list<ObjectRef> vulner;
};

#endif
