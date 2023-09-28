#pragma once

// Author: Garry Morrison
// Added: 2023-9-26
// Updated: 2023-9-26

#include <vector>
#include <iostream>
// #include "../../SemantiKet.h"
#include "AST.h"
// #include "../Parser/token.h"
#include "../Parser/Serial.h"
// #include "AST.h"
#include "NodeType.h"

extern Serial serial;

namespace SKet {

	// class yyTOKEN;

	class Internal : public AST
	{
	public:
		int id = -1;
		NodeType ntype;
		// yyTOKEN tok;
		size_t nkids = 0;
		std::vector<AST*> kids;

		Internal(AST* t1);

		// Enable a bit later.
		virtual void accept(ASTVisitor& V) override {
			V.visit(*this);
		}
		
	};

};
