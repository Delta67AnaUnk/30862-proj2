#ifndef _ZORK_MAP_
#define _ZORK_MAP_

#include <functional>
#include "Object.hpp"
#include <map>

using namespace std;

class Map
{
public:
	typedef map<string,ObjRef > map_table;
	typedef pair<string,ObjRef > map_element;
	static Map();

	Object& get(string& sth)
	{
		const map_table::iterator it;
		it = obj.find(sth);
		if(it==obj.end())
			return NULL;
		else
			return it->second;
	}
	
	void add(string& name, Object& sth)
	{obj.insert(map_element(name,sth));}
	
	void remove(string& name)
	{obj.erase(name);}

private:
	static map_table obj;
};


#endif
