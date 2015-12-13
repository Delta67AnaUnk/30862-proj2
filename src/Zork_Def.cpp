#include "Zork_Def.hpp"
#include <vector>
#include "Object.hpp"
#include "Room.hpp"
#include "Container.hpp"
#include "Creature.hpp"
#include "Item.hpp"
#include "Map.hpp"
#include "main.hpp"

using namespace std;

vector<string> WordParser(const string &input)
{
	vector<string> rtvl;
	size_t found,pre;
	string tmp;
	pre = 0;
	found = input.find_first_of(' ');
	while(found!=string::npos){
		tmp = string(input,pre,found);
		rtvl.push_back(tmp);
		pre = found;
		found = input.find_first_of(' ',found+1);
	}
	if(rtvl[0] == "turn"){
		rtvl[0] = "turn on";
		rtvl.erase(rtvl.begin()+1);
	}
	return rtvl;
}

Action ActionParser(const string& input)
{
	vector<string> str = WordParser(input);
	Action rtvl;
	Object& obj = ZorkMap->get(str[1]);
	reference_wrapper<Object> Obj = ref(obj);
	if(str[0]=="Update"){
		string newstate = str[3];
		rtvl = [Obj,newstate](const string& s){
			Obj.get().Update(newstate);
		};
	}else if(str[0]=="Add"){
		Object& owner = ZorkMap->get(str[3]);
		reference_wrapper<Object> Owner = ref(owner);
		rtvl = [Obj,Owner](const string& s){
			Owner.get().Add(Obj);
		};
	}else if(str[0]=="Delete"){
		rtvl = [Obj](const string& s){
			Obj.get().Delete();
		};
	}else if(str[0]=="Remove"){
		Object& owner = ZorkMap->get(str[3]);
		reference_wrapper<Object> Owner = ref(owner);
		rtvl = [Obj,Owner](const string& s){
			Owner.get().Remove(Obj);
		};
	}else{
		rtvl = [Obj,input](const string& s){
			Obj.get().React(input);
		};
	}
	return rtvl;
}

Condition ConditionParser(const string& obj,const string& status)
{
	reference_wrapper<Object> Obj = ref(ZorkMap->get(obj));
	return [Obj,status](){
		return (Obj.get().getstatus())==status;
	};
}

Condition ConditionParser(bool has,const string& obj,const string& owner)
{
	reference_wrapper<Object> Obj = ref(ZorkMap->get(obj));
	reference_wrapper<Object> Owner = ref(ZorkMap->get(owner));
	return [Obj,Owner,has](){
		return has^(Owner.get().Has(Obj.get()));
	};
}

void CommandParser(const string& cmd)
{
	vector<string> str = WordParser(cmd);
	if(str[0]=="n"||str[0]=="s"||str[0]=="e"||str[0]=="w"){
		ZorkMap->getCurrentRoom().React(cmd);
	}else if(str[0]=="i"){
		ZorkMap->getInventory().PrintItem();
	}else{
		ZorkMap->get(str[1]).React(cmd);
	}
}

