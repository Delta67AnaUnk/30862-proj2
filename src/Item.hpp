#ifndef _ZORK_ITEM_
#define _ZORK_ITEM_

#include <list>
#include "Object.hpp"
#include "Zork_Def.hpp"

using namespace std;

class Item:public Object
{
public:
	Item(const string& n, const string& desc, const string& status,bool enable);

	void addTurnon(string& prt,
	list<Action>::iterator s1,
	list<Action>::iterator e1);

private:
	bool turnon;
};

#endif
