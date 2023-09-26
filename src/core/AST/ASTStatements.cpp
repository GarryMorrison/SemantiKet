#include "ASTStatements.h"

namespace SKet {

	ASTStatements::ASTStatements(AST* t1) 
	{
		id = serial.get_id();
		ntype = NodeType::statements;
		if (t1)
		{
			kids.push_back(t1);
			nkids++;
		}
	}

	void ASTStatements::print(int level)
	{
		AST::print(level);
	}

};