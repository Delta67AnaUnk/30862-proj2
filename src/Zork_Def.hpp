#ifndef _ZORK_DEF_
#define _ZORK_DEF_

#include <functional>
#include <list>

using namespace std;

typedef function<void(string&)> Action;
typedef function<bool()> Condition;

list<string> WordParser(string &input);
Action ActionParser(string& input);
Condition ConditionParser(string& obj,string& status);
Condition ConditionParser(bool has,string& obj,string& owner);

#endif
