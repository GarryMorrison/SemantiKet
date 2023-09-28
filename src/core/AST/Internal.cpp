#include "Internal.h"

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

namespace SKet {

	Internal::Internal(AST* t1) 
	{
		id = serial.get_id();
		ntype = NodeType::Internal;
		if (t1)
		{
			kids.push_back(t1);
			nkids++;
		}
	}

	Internal::Internal(AST* t1, AST* t2)
	{
		id = serial.get_id();
		ntype = NodeType::Internal;
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
	}

	Internal::Internal(AST* t1, AST* t2, AST* t3)
	{
		id = serial.get_id();
		ntype = NodeType::Internal;
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
	Internal::Internal(AST* t1, AST* t2, AST* t3, AST* t4)
	{
		id = serial.get_id();
		ntype = NodeType::Internal;
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
