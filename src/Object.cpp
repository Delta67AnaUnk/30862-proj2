#include "Object.hpp"
#include "Trigger.hpp"
#include <functional>

using namespace std;

int Object::maxhandle = 0;

void Object::React(const string& cmd)
{
	list<Trigger>::iterator i;
	check = true;
	while(check){
		check = false;
		for(i=tri.begin();i!=defaultEvents;++i){
			check &= i->run(cmd);
			if(!i->isPerm()){
				tri.erase(i--);
			}
		}
	}
	check = true;
	while(check){
		check = false;
		for(i = defaultEvents;i!=tri.end();++i){
			check &= i->run(cmd);
			if(!i->isPerm()){
				tri.erase(i--);
			}
		}
	}
}

