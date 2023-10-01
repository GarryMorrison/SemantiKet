#pragma once

// Author: Garry Morrison
// Added: 2023-10-1
// Updated: 2023-10-1

#include <iostream>
#include "../AST/Leaf.h"
#include "../AST/Internal.h"
#include "../AST/Root.h"
#include "ASTVisitor.h"
// #include "../misc/misc.h"
#include "../SymTable/Symbol.h"
#include "../SymTable/SymTable.h"

// namespace SKet??

namespace SKet {

	class MakeSymbolTables : public ASTVisitor {
	public:
		Scope* sc = nullptr;
		MakeSymbolTables(Scope* scope) { sc = scope; }
		virtual void visit(Leaf& Node) override {
			if (sc)
			{
				sc->define(new VariableSymbol(Node.tok));
			}
		}
		virtual void visit(Internal& Node) override {
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
		}
		virtual void visit(Root& Node) override { visit(static_cast<Internal&>(Node)); }
	};

}
