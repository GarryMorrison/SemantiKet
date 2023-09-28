#pragma once

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

#include "AST.h"
#include "../Parser/token.h"
#include "../Parser/Serial.h"
#include "NodeType.h"

extern Serial serial;

namespace SKet {

	class yyTOKEN;

	class Leaf : public AST
	{
	public:
		int id = -1;
		NodeType ntype;
		yyTOKEN tok;
		// size_t nkids = 0;
		// std::vector<AST*> kids;

		Leaf(yyTOKEN token);

		// Enable a bit later.
		virtual void accept(ASTVisitor& V) override {
			V.visit(*this);
		}
		
	};

};