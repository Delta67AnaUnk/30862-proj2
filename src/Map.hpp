#ifndef _ZORK_MAP_
#define _ZORK_MAP_

#include <functional>
#include "Object.hpp"
#include "Container.hpp"
#include "Room.hpp"
#include <map>

using namespace std;

class Map
{
public:
	typedef map<string,Object> map_table;
	typedef pair<string,Object> map_element;
	Map(const string& filename);

	Object& get(const string& sth) 
	{
		map_table::iterator it;
		it = obj.find(sth);
		if(it==obj.end())
			return NullObj;
		else
			return it->second;
	}
	
	void add(string& name, Object& sth)
	{obj.insert(map_element(name,sth));}
	
	void remove(string& name)
	{obj.erase(name);}

	void Win(const string& s)
	{cout<<"You found the exit!\nYou are safe now."<<endl;}
	
	void Move(const string& nextroom)
	{CurRoomPtr = ref(get(nextroom));}

	Object& getCurrentRoom(){return CurRoomPtr.get();}
	const Object& getCurrentRoom() const{return CurRoomPtr.get();}

	Container& getInventory(){return Inventory;}
	const Container& getInventory() const{return Inventory;}

	void Run();

private:
	map_table obj;
	reference_wrapper<Room> CurRoomPtr;
	Container Inventory;

};


#endif
