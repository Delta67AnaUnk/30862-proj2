#include "Object.hpp"
#include "Trigger.hpp"
#include <functional>

void Object::React()
{
	list<Trigger>::iterator i;
	check = true;
	while(check){
		check = false;
		for(i=tri.begin();i!=tri.end();++i){
			if(i->getCMD()) continue;
			check &= i->run(NULL);
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
		if(i->getCMD()){
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
