#ifndef _ZORK_ROOM_
#define _ZORK_ROOM_

#include "Object.hpp"
#include "Container.hpp"
#include "Item.hpp"
#include "Creature.hpp"
#include <functional>
#include <list>

using namespace std;

class Room:public Object
{
public:
	Room(const string& n,const string& desc,const string& status, const string& type);

	void addBorder(string& rm,int dir){border[dir] = rm;}
	void removeBorder(int dir){border[dir].clear();}

	static int Border(char c){
		switch(c){
		case 'n':
			return 0;
		case 'e':
			return 1;
		case 's':
			return 2;
		case 'w':
			return 3;
		}
		return -1;
	}

	void Add(Object& c);
	void Delete();
	bool Has(const Object& c) {return c.getowner()==*this;}
	void Remove(Object& c);

private:
	string type;
	string border[4];//NESW
	list< reference_wrapper<Container> > cont;
	list< reference_wrapper<Item> > item;
	list< reference_wrapper<Creature> > being;
};

#endif
