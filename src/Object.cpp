#include "Object.hpp"
#include "Trigger.hpp"
#include <functional>

using namespace std;

int Object::maxhandle = 0;

void Object::React()
{
	list<Trigger>::iterator i;
	check = true;
	while(check){
		check = false;
		for(i=tri.begin();i!=tri.end();++i){
			if(i->getCMD().empty()) continue;
			string tmp;
			check &= i->run(tmp);
			if(!i->isPerm()){
				tri.erase(i--);
			}
		}
	}
}

void Object::React(string& cmd)
{
	list<Trigger>::iterator i;
	check = false;
	for(i=tri.begin();i!=tri.end();++i){
		if(i->getCMD().empty()){
			if(cmd.find(i->getCMD())==string::npos)
				continue;
		}else continue;
		check &= i->run(cmd);
		if(!i->isPerm()){
			tri.erase(i--);
		}
	}
	if(check)React();
}

