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
#include "../AST/GlobalAssignment.h"
#include "../AST/FunctionDefinition.h"
#include "../AST/Chunk.h"
#include "ASTVisitor.h"
// #include "../misc/misc.h"
#include "../Symbol/BaseSymbol.h"
#include "../SymTable/SymbolTable.h"
#include "../ScopedSymbol/ContextSymbol.h"
#include "../ScopedSymbol/FunctionSymbol.h"

// namespace SKet??

namespace SKet {

	class MakeSymbolTables : public ASTVisitor {
	public:
		// BaseScope* sc = nullptr;
		// MakeSymbolTables(BaseScope* scope) { sc = scope; }
		BaseScope* globalScope = nullptr;
		BaseScope* currentScope = nullptr;
		ContextSymbol* currentContext = nullptr;
		MakeSymbolTables(SymbolTable* symtab) { 
			if (symtab)  // we should error if symtab is nullptr!
			{
				globalScope = symtab->globalScope;
				currentScope = symtab->globalScope;
				/*
				BaseScope* tmp = currentScope->resolveContext("#global"); // switch to #global context
				if (tmp)
				{
					currentScope = tmp;
				}
				*/
				currentContext = currentScope->resolveContext("#global"); // switch to #global context
				if (currentContext)
				{
					currentScope = currentContext;
				}
			}
		}
		virtual void visit(Leaf& node) override {
			if (currentScope)
			{
				// sc->define(new VariableSymbol(node.tok));
				currentScope->define(BaseSymbol::Construct(node.tok));
			}
		}
		virtual void visit(Internal& node) override {
			for (AST* tree : node.getKids())
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
		}

		virtual void visit(Root& node) override {
			for (AST* tree : node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
		}

		virtual void visit(ContextAssignment& node) override
		{
			// std::cout << "Context Assignment\n";
			if (node.nkids < 2) // if not complete, then do nothing. Maybe error later?
			{
				return;
			}
			if (node.nkids == 2)
			{
				if (node.kids[0] && node.kids[1])
				{
					if (node.kids[0]->getNType() == Node::NType::Leaf && node.kids[1]->getNType() == Node::NType::Leaf)
					{
						yyTOKEN token = node.kids[0]->getToken();
						std::string label = node.kids[1]->getToken().text;
						std::cout << "line " << token.line << ": def context " << token.text << " " << label << "\n";
						// currentScope->defineContext(new ContextSymbol(token.text, label, currentScope));
						// globalScope->defineContext(new ContextSymbol(token.text, label, globalScope)); // Make context's global, unless specified otherwise with #context1.#subcontext = |sub context>
						globalScope->defineContext(new ContextSymbol(token.text, label, globalScope, currentContext)); // Make context's global, unless specified otherwise with #context1.#subcontext = |sub context>

						// Follow a context define, with a context switch:
						/*
						BaseScope* tmp = globalScope->resolveContext(token.text); // Error if token.text is not a known context!
						if (tmp)
						{
							currentScope = tmp;
						}
						*/
						currentContext = globalScope->resolveContext(token.text); // Error if token.text is not a known context!
						if (currentContext)
						{
							currentScope = currentContext;
						}
					}
					// std::cout << "NType 0: " << Node::to_string(node.kids[0]->getNType()) << "\n";
					// std::cout << "NType 1: " << Node::to_string(node.kids[1]->getNType()) << "\n";
				}
			}
		}

		virtual void visit(ContextSwitch& node) override
		{
			// std::cout << "Context Switch\n";
			/*
			if (node.nkids == 1)
			{
				if (node.kids[0])
				{
					yyTOKEN token = node.kids[0]->getToken();
					if (token.text == "#parent")
					{
						std::cout << "line " << token.line << ": parent context switch ref " << token.text << "\n";
						BaseScope* tmp = currentScope->getEnclosingScope();
						if (tmp)
						{
							currentScope = tmp;
						}
					}
					else
					{
						std::cout << "line " << token.line << ": context switch ref " << token.text << "\n";  // Error if token.text is not a known context!
						// currentScope = currentScope->resolveContext(token.text); // null pointer deref if context not defined!
						
						BaseScope* tmp = currentScope->resolveContext(token.text);
						if (tmp)
						{
							currentScope = tmp;
						}
					}
				}
			}
			*/
			
			if (node.nkids == 1 && node.kids[0])
			{
				yyTOKEN token = node.kids[0]->getToken();
				std::cout << "line " << token.line << ": context switch ref " << token.text << "\n";
				/*
				BaseScope* tmp = globalScope->resolveContext(token.text); // Error if token.text is not a known context!
				if (tmp)
				{
					currentScope = tmp;
				}
				*/
				currentContext = globalScope->resolveContext(token.text);
				if (currentContext)
				{
					currentScope = currentContext;
				}
			}
			
			/*
			if (node.nkids == 1 && node.kids[0])
			{
				yyTOKEN token = node.kids[0]->getToken();
				std::cout << "line " << token.line << ": context switch ref " << token.text << "\n";
				BaseScope* tmp;
				if (token.text == "#parent")
				{
					tmp = currentScope->getEnclosingScope();
				}
				else
				{
					tmp = globalScope->resolveContext(token.text); // Error if token.text is not a known context!
				}
				if (tmp)
				{
					currentScope = tmp;
				}
			}
			*/
		}

		virtual void visit(Assignment& node) override
		{
			// std::cout << "Assignment\n";
			if (node.nkids > 1 && node.kids[0])
			{
				yyTOKEN token = node.kids[0]->getToken();
				std::cout << "line " << token.line << ": def " << token.text << "\n";
				currentScope->define(BaseSymbol::Construct(token));
			}
		}

		
		virtual void visit(GlobalAssignment& node) override
		{
			// std::cout << "GlobalAssignment\n";
			if (node.nkids > 1 && node.kids[0])
			{
				yyTOKEN token = node.kids[0]->getToken();
				std::cout << "line " << token.line << ": def " << token.text << "\n";
				currentContext->define(BaseSymbol::Construct(token)); // are we defining in the right scope?
			}
		}
		

		virtual void visit(FunctionDefinition& node) override
		{
			// std::cout << "Function Definition\n";
			if (node.nkids > 1 && node.kids[0])
			{
				yyTOKEN token = node.kids[0]->getToken();
				std::cout << "line " << token.line << ": fn def: " << token.text << "\n";
				// currentScope->define(new FunctionSymbol(node, currentScope));
				FunctionSymbol* tmp = new FunctionSymbol(node, currentScope);
				currentScope->define(tmp);
				if (tmp)
				{
					currentScope = tmp;
					if (node.nkids >= 3)
					{
						AST* tree = node.kids[node.nkids - 1];
						if (tree)
						{
							tree->accept(*this);
						}
					}
					currentScope = currentScope->getEnclosingScope();
				}
			}
		}

		// virtual void visit(Chunk& Node) override { visit(static_cast<Internal&>(Node)); } // Do more here later!
	};

}
