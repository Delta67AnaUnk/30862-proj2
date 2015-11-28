#ifndef _ZORK_ROOM_
#define _ZORK_ROOM_

#include "Object.hpp"
#include <list>

using namespace std;

class Room:public Object
{
public:
	Room(string& n,string& desc,string& status, string& type):
	Object(n,desc,status),type(type)
	{
		Trigger trig = Trigger("open" );
	}

	void addBorder(string& rm,int dir){border[dir] = rm;}
	void removeBorder(int dir){border[dir] = NULL;}
	
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

	void Add(ObjRef c)
	{
		item.push_back(c);
		c.addBelong(*this);
	}

	void Delete()
	{
		int i = 0;
		for(i = 0;i<4;i++){
			if(border[i]){
				Room& rm = (Room&)ZorkMap.get(border[i]);
				rm.removeBorder((i+2)%4);
			}
		}
	}

	bool Has(Object& c)
	{
		return c.isBelong(*this);
	}

	void RemoveFrom(ObjRef c)
	{
		if(!Has(c)) return;
		list<decltype(c)>::iterator i;
		list<decltype(c)>* ls;
		if(typeid(c).name()=="Container"){
			ls = &cont;
		}else if(typeid(c).name()=="Item"){
			ls = &item;
		}else if(typeid(c).name()=="Creature"){
			ls = &being;
		}
		for(i=ls->begin();i!=ls->end();i++){
			if(*i==c) break;
		}
		ls->erase(i);
	}

private:
	string type;
	string border[4];//NESW
	list<Container> cont;
	list<Item> item;
	list<Creature> being;
};

#endif
