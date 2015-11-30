#include "Zork_Def.hpp"
#include <list>
#include "Object.hpp"
#include "Map.hpp"

using namespace std;

Map ZorkMap;

list<string> WordParser(string &input)
{
	list<string> rtvl;
	size_t found,pre;
	string tmp;
	pre = 0;
	found = input.find_first_of(' ');
	while(found!=string::npos){
		tmp = string(input+pre,found-pre);
		rtvl.push_back(tmp);
		pre = found;
		found = input.find_first_of(' ',found+1);
	}
	return rtvl;
}

Action ActionParse(string& input)
{
	list<string> str = wordparser(input);
	Action rtvl;
	if(act=="Game Over"){
		ZorkMap.Win();
		return NULL;
	}
	Object& Obj = ZorkMap.get(str[1]);
	if(str[0]=="Update"){
		rtvl = [=](){
			Obj.Update(str[3];);
		};
	}else if(str[0]=="Add"){
		rtvl = [=](){
			Object& owner = ZorkMap.get(str[3]);
			owner.Add(Obj);
		};
	}else if(str[0]=="Delete"){
		rtvl = [=](){
			Obj.Delete();
		};
	}
	return rtvl;
}

Condition ConditionParser(string& obj,string& status)
{
	return [=](){
		return (ZorkMap.get(obj).getstatus())==status;
	};
}

Condition ConditionParser(string& has,string& obj,string& owner)
{
	return [=](){
		bool b = false;
		if(has=="yes") b==true;
		Object Owner = ZorkMap.get(owner);
		Object Obj = ZorkMap.get(obj);
		return b^(Owner.Has(Obj));
	};
}
