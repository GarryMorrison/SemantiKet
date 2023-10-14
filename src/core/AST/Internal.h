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
		std::string sym;
		int rule_id = -1;
		int id = -1;
		// NodeType ntype;
		Node::NType ntype = Node::NType::Internal;
		// yyTOKEN tok;
		size_t nkids = 0;
		std::vector<AST*> kids;

		// Internal() {}
		Internal(AST* t1);
		Internal(AST* t1, AST* t2);
		Internal(AST* t1, AST* t2, AST* t3);
		Internal(AST* t1, AST* t2, AST* t3, AST* t4);

		Internal(Node::NType type, AST* t1) : Internal(t1) { ntype = type; }
		Internal(Node::NType type, AST* t1, AST* t2) : Internal(t1, t2) { ntype = type; }
		Internal(Node::NType type, AST* t1, AST* t2, AST* t3) : Internal(t1, t2, t3) { ntype = type; }
		Internal(Node::NType type, AST* t1, AST* t2, AST* t3, AST* t4) : Internal(t1, t2, t3, t4) { ntype = type; }

		Internal(const std::string& s, int id, AST* t1) : Internal(t1) { sym = s; rule_id = id; }
		Internal(const std::string& s, int id, AST* t1, AST* t2) : Internal(t1, t2) { sym = s; rule_id = id; }
		Internal(const std::string& s, int id, AST* t1, AST* t2, AST* t3) : Internal(t1, t2, t3) { sym = s; rule_id = id; }
		Internal(const std::string& s, int id, AST* t1, AST* t2, AST* t3, AST* t4) : Internal(t1, t2, t3, t4) { sym = s; rule_id = id; }

		// std::string type_to_string();  // Put this here or in AST class?
		std::string to_string();  // Put this here or in AST class?


		virtual void accept(ASTVisitor& V) override {
			V.visit(*this);
		}
		
	};

};
