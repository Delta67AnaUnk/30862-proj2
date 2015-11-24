#ifndef _ZORK_ITEM_
#define _ZORK_ITEM_

#include <string>
using namespace std;

class Item:public Object
{
public:
	Item(string& n,string&desc, string& status,bool enable,string& wrt):Object(n,desc,status),writing(wrt),turnon(enable);

	void Turnon()
	{
		if(!turnon) 
			cout<<"Not applicable for this item."<<endl;
		else{
			turned_on = true;
			runTriggers();
		}
	}


private:
	bool turnon;
	bool turned_on;
	string writing;
};

#endif
