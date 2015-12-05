#ifndef _ZORK_CONTAINER_
#define _ZORK_CONTAINER_

#include "Object.h"
#include <list>
#include <functional>

using namespace std;

class Container:public Object
{
public:
	Container(string& n,string& desc.string& status):
	Object(n,desc,status);

	void addAccept(Object& c) {accept.push_front(ref(c));}

	void Add(Object& c);
	void Delete();
	bool Has(Object& c) {return c.getowner()==*this;}
	void Remove(Object& c);

private:
	list< reference_wrapper<Item> > item;
	list< reference_wrapper<Item> > accept;
};


#endif
