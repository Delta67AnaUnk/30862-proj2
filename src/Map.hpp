#ifndef _ZORK_MAP_
#define _ZORK_MAP_

#include <functional>
#include "Zork_Def.hpp"
#include "Object.hpp"
#include "Container.hpp"
#include "Room.hpp"
#include <map>
#include "rapidxml/rapidxml.hpp"

using namespace std;
using namespace rapidxml;

string emptystr;
Object NullObj(emptystr,emptystr,emptystr);

class Map
{
public:
	typedef map<string,Object> map_table;
	typedef pair<string,Object> map_element;
	typedef map<string,xml_node<>*> map_xml;
	typedef pair<string,xml_node<>*> map_xml_element;

	Map():winflag(false),CurRoomPtr(NULL),Inventory(NULL){}

	void loader(const string& filename);

	Object& get(const string& sth) 
	{
		map_table::iterator it;
		it = obj.find(sth);
		if(it==obj.end())
			return NullObj;
		else
			return it->second;
	}
	
	xml_node<>* getnode(const string& sth)
	{
		map_xml::iterator it;
		it = objload.find(sth);
		if(it==objload.end())
			return NULL;
		else 
			return it->second;
	}

	void add(const string& name, Object& sth)
	{obj.insert(map_element(name,sth));}
	
	void addnode(const string& name, xml_node<>* i)
	{objload.insert(map_xml_element(name,i));}

	void remove(string& name)
	{obj.erase(name);}

	void Win(const string& s)
	{
		cout<<"You found the exit!\nYou are safe now."<<endl;
		winflag = true;
	}
	
	bool isRunning(){return !winflag;}

	void Move(const string& nextroom)
	{
		//CurRoomPtr = ref(dynamic_cast<Room&>(get(nextroom)));
		CurRoomPtr = &((Room&)get(nextroom));
		cout<<getCurrentRoom().getname()<<endl;
		cout<<getCurrentRoom().getdescrip()<<endl;
	}

	Object& getCurrentRoom(){return *CurRoomPtr;}
	const Object& getCurrentRoom() const{return *CurRoomPtr;}

	Container& getInventory(){return *Inventory;}
	const Container& getInventory() const{return *Inventory;}

	void Run();

private:
	map_table obj;
	map_xml objload;
	//reference_wrapper<Room> CurRoomPtr;
	Room* CurRoomPtr;
	Container* Inventory;
	bool winflag;

	void parseRoom2(xml_node<>* i, Room& rm);
	void parseItem2(xml_node<>* i, Item& it);
	void parseContainer2(xml_node<>* i, Container& ct);
	void parseCreature2(xml_node<>* i, Creature& cr);

	static Room parseRoom(xml_node<>* i);
	static Item parseItem(xml_node<>* i);
	static Creature parseCreature(xml_node<>* i);
	static Container parseContainer(xml_node<>* i);
	
	static Condition parseCondition(xml_node<>* i);
	static Trigger parseTrigger(xml_node<>* i);
};


#endif
