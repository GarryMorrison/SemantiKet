#include "FunctionDefinition.h"

// Author: Garry Morrison
// Added: 2023-10-29
// Updated: 2023-10-29

namespace SKet {

	FunctionDefinition::FunctionDefinition(AST* t1, AST* t2, AST* t3)
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

	FunctionDefinition::FunctionDefinition(AST* t1, AST* t2, AST* t3, AST* t4)
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
		if (t4)
		{
			kids.push_back(t4);
			nkids++;
		}
	}
};
