#include "Root.h"

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

namespace SKet {

	Root::Root(AST* t1)
	{
		id = serial.get_id();
		ntype = NodeType::Root;
		if (t1)
		{
			kids.push_back(t1);
			nkids++;
		}
	}
};
