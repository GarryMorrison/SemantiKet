#pragma once

// Author: Garry Morrison
// Added: 2023-9-26
// Updated: 2023-9-26

#include <vector>
// #include "../../SemantiKet.h"
#include "AST.h"
#include "../Parser/token.h"
#include "../Parser/Serial.h"
// #include "AST.h"

extern Serial serial;

namespace SKet {

	class yyTOKEN;

	class ASTStatements : public AST
	{
	public:
		int id = -1;
		NodeType ntype;
		size_t nkids = 0;
		yyTOKEN tok;
		std::vector<AST*> kids;

		ASTStatements(AST* t1);

		void print(int level);
		void print() { print(0); }
	};

};
