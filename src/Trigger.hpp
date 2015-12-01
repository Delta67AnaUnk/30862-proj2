#ifndef _ZORK_TRIGGER_
#define _ZORK_TRIGGER_

#include "Zork_Def.hpp"
#include <list>
#include <iostream>
#include <string>

using namespace std;


class Trigger
{
public:
	Trigger(const string& com, const string& prt,bool permenant):command(com),print(prt),type(permenant){}

	void addAction(Action act){action.push_front(act);}
	void addCondition(Condition cd){cond.push_front(cd);}

	const string& getCMD() const {return command;}
	const bool isPerm() const {return type;}
	const string& getprint() const {return print;}

	bool run(const string& input)
	{
		list<Condition>::iterator i;
		// check if conditions meets
		for(i=cond.begin();i!=cond.end();++i){
			if(!(*i)()){
				return false;
			}
		}
		// run logic
		cout<<print<<endl;
		list<Action>::iterator t;
		for(t=action.begin();t!=action.end();++t){
			(*t)(input);
		}
		return true;
	}

private:
	bool type;
	string command;
	string print;
	list<Action> action;
	list<Condition> cond;
};

#endif
