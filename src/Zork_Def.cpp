#include "Zork_Def.hpp"
#include "Zork_main.hpp"
#include <list>
#include "Object.hpp"
#include "Map.hpp"

using namespace std;

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
	list<string> str = WordParser(input);
	Action rtvl;
	if(act=="Game Over"){
		return ZorkMap.Win;
	}
	Object& Obj = ZorkMap.get(str[1]);
	if(str[0]=="Update"){
		rtvl = [this](string& s){
			Obj.Update(str[3];);
		};
	}else if(str[0]=="Add"){
		rtvl = [this](string& s){
			Object& owner = ZorkMap.get(str[3]);
			owner.Add(Obj);
		};
	}else if(str[0]=="Delete"){
		rtvl = [this](string& s){
			Obj.Delete();
		};
	}else if(str[0]=="Remove"){
		rtvl = [this](string& s){
			Object& owner = ZorkMap.get(str[3]);
			owner.Remove(Obj);
		};
	}
	return rtvl;
}

Condition ConditionParser(string& obj,string& status)
{
	return [this](){
		return (ZorkMap.get(obj).getstatus())==status;
	};
}

Condition ConditionParser(string& has,string& obj,string& owner)
{
	return [this](){
		bool b = false;
		if(has=="yes") b==true;
		Object Owner = ZorkMap.get(owner);
		Object Obj = ZorkMap.get(obj);
		return b^(Owner.Has(Obj));
	};
}
