#pragma once

// Author: Garry Morrison
// Added: 2023-10-29
// Updated: 2023-10-29

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

	class FunctionDefinition : public Internal
	{
	public:
		int id = -1;
		Node::NType ntype = Node::NType::FunctionDefinition;
		// yyTOKEN tok;
		size_t nkids = 0;
		std::vector<AST*> kids;

		FunctionDefinition(AST* t1, AST* t2, AST* t3);
		FunctionDefinition(AST* t1, AST* t2, AST* t3, AST* t4);
		Node::NType getNType() { return ntype; }
		std::string to_string() { return Node::to_string(ntype); }

		virtual void accept(ASTVisitor& V) override {
			V.visit(*this);
		}

	};

};