#ifndef _ZORK_CREATURE_
#define _ZORK_CREATURE_

#include "Object.hpp"
#include <List>
#include <functional>

using namespace std;

class Creature:public Object
{
public:
	Creature(string& n,string& desc, string& status):
	Object(n,desc,status);

	void addVul(Object& obj){vulner.push_back(obj);}

private:
	List<reference_wrapper<Object> > vulner;
	List<auto> attack;
};

#endif
