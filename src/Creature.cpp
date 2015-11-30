#include "Creature.hpp"

void Creature::addAttack(string& prt,
	list<Condition>::iterator s1,
	list<Condition>::iterator e1,
	list<Action>::iterator s2,
	list<Action>::iterator e2)
{
	Trigger trig = Trigger("attack",prt,true);
	list<Condition>::iterator i;
	for(i=s1;i!=e1;++i){
		trig.addCondition(*i);
	}
	list<Action>::iterator t;
	for(t=s2;t!=e2;++t){
		trig.addAction(*t);
	}
	addTrigger(trig);
}
