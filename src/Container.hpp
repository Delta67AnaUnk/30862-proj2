#ifndef _ZORK_CONTAINER_
#define _ZORK_CONTAINER_

#include "Object.hpp"
#include "Item.hpp"
#include <list>
#include <functional>

using namespace std;

class Container:public Object
{
public:
	Container(const string& n, const string& desc, const string& status);

	void addAccept(Item& c) {
		reference_wrapper<Item> cre = ref(c);
		accept.push_front(cre);
	}

	void Add(Object& c);
	void Delete();
	bool Has(const Object& c) {return c.getowner()==*this;}
	void Remove(Object& c);

private:
	list< reference_wrapper<Item> > item;
	list< reference_wrapper<Item> > accept;
};


#endif
