#ifndef _ZORK_CONDITION_
#define _ZORK_CONDITION_

#include <functional>
#include <list>
#include "Map.hpp"

using namespace std;

typedef function<void()> Action;
typedef function<bool()> Condition;

list<string> WordParser(string &input);
Action ActionParser(string& input);
Condition ConditionParser(string& obj,string& status);
Condition ConditionParser(bool has,string& obj,string& owner);

extern Map ZorkMap;

#endif
