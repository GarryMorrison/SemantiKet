#include "LearnRule.h"

// Author: Garry Morrison
// Added: 2023-11-7
// Updated: 2023-11-7

namespace SKet {

	LearnRule::LearnRule(AST* t1, AST* t2, AST* t3)
	{
		id = serial.get_id();
		if (t1)
		{
			kids.push_back(t1);
			nkids++;
		}
		if (t2)
		{
			kids.push_back(t2);
			nkids++;
		}
		if (t3)
		{
			kids.push_back(t3);
			nkids++;
		}
	}

};