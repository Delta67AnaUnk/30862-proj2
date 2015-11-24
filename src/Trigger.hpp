#ifndef _ZORK_TRIGGER_
#define _ZORK_TRIGGER_

#include "Condition.hpp"
#include <List>
#include <iostream>
#include <string>

using namespace std;

class Trigger
{
public:
	Trigger(string& com, string& act, string& prt,bool permenant):command(com),action(act),print(prt),perm(permenant);

	void addCondition(Condition& cd)
	{cond.push_back(cd);}

	const bool isPerm() const {return perm;}

	void run()
	{
		List<Condition>::iterator i;
		// check if conditions meets
		for(i=cond.begin();i!=cond.end();++i){
			if(!i->istrue()){
				return;
			}
		}
		// run logic
		cout<<print<<endl;
		action();
	}
private:
	bool perm;
	string command;
	auto action;
	string print;
	List<Condition> cond;
};

#endif
