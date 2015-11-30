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
	Creature(string& n,string& desc, string& status):
	Object(n,desc,status);

	void addVul(Object& vul){vulner.push_back(ref(vul));}

	void addAttack(string& prt,
	list<Condition>::iterator s1,
	list<Condition>::iterator e1,
	list<Action>::iterator s2,
	list<Action>::iterator e2);

private:
	list<ObjectRef> vulner;
};

#endif
