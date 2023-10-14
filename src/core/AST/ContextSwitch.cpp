#include "ContextSwitch.h"

namespace SKet {
	ContextSwitch::ContextSwitch(AST* t1)
	{
		id = serial.get_id();
		if (t1)
		{
			kids.push_back(t1);
			nkids++;
		}
	}

};
