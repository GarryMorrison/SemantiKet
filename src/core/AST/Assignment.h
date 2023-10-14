#pragma once

// Author: Garry Morrison
// Added: 2023-10-14
// Updated: 2023-10-14

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

	class Assignment : public Internal
	{
	public:
		int id = -1;
		Node::NType ntype = Node::NType::Assignment;
		// yyTOKEN tok;
		size_t nkids = 0;
		std::vector<AST*> kids;

		Assignment(AST* t1, AST* t2) : Internal(Node::NType::Assignment, t1, t2) { }

		virtual void accept(ASTVisitor& V) override {
			V.visit(*this);
		}

	};

};