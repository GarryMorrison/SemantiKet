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

	class ContextAssignment : public Internal
	{
	public:
		int id = -1;
		Node::NType ntype = Node::NType::ContextAssignment;
		// yyTOKEN tok;
		size_t nkids = 0;
		std::vector<AST*> kids;

		// ContextAssignment(AST* t1) : Internal(Node::NType::ContextAssignment, t1) { }
		// ContextAssignment(AST* t1);
		ContextAssignment(AST* t1, AST* t2) : Internal(Node::NType::ContextAssignment, t1, t2) { }

		virtual void accept(ASTVisitor& V) override {
			V.visit(*this);
		}

	};

};