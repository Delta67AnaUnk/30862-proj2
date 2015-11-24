#ifndef _ZORK_CONDITION_
#define _ZORK_CONDITION_

class Condition
{
public:
	Condition(Object owner,Obejct obj,auto status):owner(owner),obj(obj),status(status);

	bool istrue(){
		return status();
	}

private:
	Object owner;
	Object obj;
	auto status;
};

#endif
