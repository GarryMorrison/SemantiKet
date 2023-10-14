#pragma once

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-29

#include "../Parser/token.h"
#include "../ASTVisitor/ASTVisitor.h"
#include "Node.h"


namespace SKet {

	class yyTOKEN;

	class AST
	{
	public:
		AST() {}
		Node::NType ntype = Node::NType::AST;
		yyTOKEN tok;
		virtual ~AST() {}
		virtual void accept(ASTVisitor& V) = 0;

	};

};