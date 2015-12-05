#include "Zork_Def.hpp"
#include "Zork_main.hpp"
#include <vector>
#include "Object.hpp"
#include "Map.hpp"

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
	return rtvl;
}

Action ActionParser(const string& input)
{
	vector<string> str = WordParser(input);
	Action rtvl;
	if(act=="Game Over"){
		return ZorkMap.Win;
	}
	Object& obj = ZorkMap.get(str[1]);
	reference_wrapper<Object> Obj = ref(obj);
	if(str[0]=="Update"){
		string newstate = str[3];
		rtvl = [Obj,newstate](const string& s){
			Obj.get().Update(newstate);
		};
	}else if(str[0]=="Add"){
		Object& owner = ZorkMap.get(str[3]);
		reference_wrapper<Object> Owner = ref(owner);
		rtvl = [Obj,Owner](const string& s){
			Owner.get().Add(Obj);
		};
	}else if(str[0]=="Delete"){
		rtvl = [Obj](const string& s){
			Obj.get().Delete();
		};
	}else if(str[0]=="Remove"){
		Object& owner = ZorkMap.get(str[3]);
		reference_wrapper<Object> Owner = ref(owner);
		rtvl = [Obj,Owner](const string& s){
			Owner.get().Remove(Obj);
		};
	}
	return rtvl;
}

Condition ConditionParser(const string& obj,const string& status)
{
	reference_wrapper<Object> Obj = ref(ZorkMap.get(obj));
	return [Obj,status](){
		return (Obj.get().getstatus())==status;
	};
}

Condition ConditionParser(bool has,const string& obj,const string& owner)
{
	reference_wrapper<Object> Obj = ref(ZorkMap.get(obj));
	reference_wrapper<Object> Owner = ref(ZorkMap.get(owner));
	return [Obj,Owner,has](){
		return has^(Owner.get().Has(Obj.get()));
	};
}
