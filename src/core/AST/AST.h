#pragma once

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

// #include "../../SemantiKet.h"

// #include "../Parser/token.h"
// #include "../Parser/Serial.h"
// #include "NodeType.h"

// extern Serial serial;

namespace SKet {

	// class yyTOKEN;

	class AST
	{
	public:
		/*  // first attempt, delete later!
		int id = -1;
		NodeType ntype;
		size_t nkids = 0;
		yyTOKEN tok;
		std::vector<AST*> kids;

		AST() { ntype = NodeType::standard; };
		AST(yyTOKEN t) { id = serial.get_id(), ntype = NodeType::standard; }
		void print(int level);
		void print() { print(0); }
		*/

		virtual ~AST() {}
		// virtual void accept(ASTVisitor& V) = 0;  // Enable later

	};

};