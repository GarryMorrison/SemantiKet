#pragma once

// Author: Garry Morrison
// Added: 2023-10-1
// Updated: 2023-10-1

#include <iostream>
#include "../AST/Leaf.h"
#include "../AST/Internal.h"
#include "../AST/Root.h"
#include "../AST/ContextAssignment.h"
#include "../AST/ContextSwitch.h"
#include "../AST/Assignment.h"
#include "ASTVisitor.h"
// #include "../misc/misc.h"
#include "../Symbol/BaseSymbol.h"
#include "../SymTable/SymTable.h"

// namespace SKet??

namespace SKet {

	class MakeSymbolTables : public ASTVisitor {
	public:
		BaseScope* sc = nullptr;
		MakeSymbolTables(BaseScope* scope) { sc = scope; }
		virtual void visit(Leaf& Node) override {
			if (sc)
			{
				// sc->define(new VariableSymbol(Node.tok));
				sc->define(BaseSymbol::Construct(Node.tok));
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

		virtual void visit(Root& Node) override {
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
		}

		virtual void visit(ContextAssignment& Node) override
		{
			std::cout << "Context Assignment\n";
			if (Node.nkids < 2) // if not complete, then do nothing. Maybe error later?
			{
				return;
			}
			/*
			if (Node.nkids == 2)
			{
				Leaf* left = dynamic_cast<Leaf*>(Node.kids);

			}
			*/
			if (Node.nkids == 2)
			{
				std::cout << Node.kids[0]->tok.text << "\n";  // tok.text is empty string for now. Fix!
				std::cout << Node.kids[0]->getnkids() << "\n"; // just a test
			}
		}

		virtual void visit(ContextSwitch& Node) override
		{
			std::cout << "Context Switch\n";
		}

		virtual void visit(Assignment& Node) override
		{
			std::cout << "Assignment\n";
		}

	};

}
