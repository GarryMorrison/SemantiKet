#pragma once

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-29

#include "../Parser/token.h"
#include "../ASTVisitor/ASTVisitor.h"
#include "Node.h"
#include <vector>


namespace SKet {

	class yyTOKEN;

	class AST
	{
	public:
		AST() {}
		Node::NType ntype = Node::NType::AST;
		yyTOKEN tok;
		size_t nkids = 0;
		std::vector<AST*> kids;

		virtual Node::NType getNType() { return ntype; }
		virtual yyTOKEN getToken() { return tok; }
		virtual size_t getnkids() { return nkids; }
		virtual std::vector<AST*> getKids() { return kids; }
		virtual ~AST() {}
		virtual void accept(ASTVisitor& V) = 0;

	};

	void ExtractTokensFromAST(AST* currentNode, std::vector<yyTOKEN>& tokens);
};