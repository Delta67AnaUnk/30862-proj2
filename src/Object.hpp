#ifndef _ZORK_OBJECT_
#define _ZORK_OBJECT_

#include <string>
#include "Trigger.hpp"

using namespace std;

class Object
{
public:
	Object(string& n,string& desc,string&status):
	name(n),descrip(desc),status(status);

	string& getname()
	{return name;}
	
	string& getdescrip
	{return descrip;}

	void addTrigger(Trigger& trig)
	{tri.push_back(trig);}

	void runTriggers()
	{
		List<Trigger>::iterator i;
		for(i=tri.begin();i!=tri.end();++i){
			i->run();
			if(!i->isPerm){
				tri.erase(i);
				i--;
			}
		}
	}

	void update(string& news)
	{status = news;}

	string& Status()
	{return status;}

private:
	string name;
	string descrip;
	string status;
	List<Trigger> tri;
}

#endif
