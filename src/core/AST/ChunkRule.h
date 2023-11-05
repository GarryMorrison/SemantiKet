#pragma once

// Author: Garry Morrison
// Added: 2023-11-6
// Updated: 2023-11-6

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

	class ChunkRule : public Internal
	{
	public:
		int id = -1;
		Node::NType ntype = Node::NType::ChunkRule;
		// yyTOKEN tok;
		size_t nkids = 0;
		std::vector<AST*> kids;

		ChunkRule(AST* t1, AST* t2, AST* t3);
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