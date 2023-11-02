#pragma once

// Author: Garry Morrison
// Added: 2023-11-2
// Updated: 2023-11-2

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

	class GlobalAssignment : public Internal
	{
	public:
		int id = -1;
		Node::NType ntype = Node::NType::GlobalAssignment;
		// yyTOKEN tok;
		size_t nkids = 0;
		std::vector<AST*> kids;

		GlobalAssignment(AST* t1, AST* t2);
		
		int getID() { return id; }
		Node::NType getNType() { return ntype; }
		size_t getnkids() { return nkids; }
		std::vector<AST*> getKids() { return kids; }
		std::string to_string() { return Node::to_string(ntype); }

		virtual void accept(ASTVisitor& V) override {
			V.visit(*this);
		}

	};

};