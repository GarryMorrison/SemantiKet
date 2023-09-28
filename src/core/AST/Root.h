#pragma once

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

#include <vector>
#include <iostream>
// #include "../../SemantiKet.h"
#include "AST.h"
// #include "../Parser/token.h"
#include "../Parser/Serial.h"
#include "NodeType.h"
#include "Internal.h"

extern Serial serial;

namespace SKet {

	// class yyTOKEN;

	class Root : public Internal
	{
	public:
		int id = -1;
		NodeType ntype;
		// yyTOKEN tok;
		size_t nkids = 0;
		std::vector<AST*> kids;

		Root(AST* t1);

		virtual void accept(ASTVisitor& V) override {
			V.visit(*this);
		}

	};

};