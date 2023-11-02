#pragma once

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-29

#include <iostream>
#include "../AST/Leaf.h"
#include "../AST/Internal.h"
#include "../AST/Root.h"
#include "../AST/ContextAssignment.h"
#include "../AST/ContextSwitch.h"
#include "../AST/Assignment.h"
#include "../AST/GlobalAssignment.h"
#include "../AST/FunctionDefinition.h"
#include "ASTVisitor.h"
#include "../misc/misc.h"

extern NodeTypeMap node_type;

namespace SKet {

	class PrintTree : public ASTVisitor {
	public:
		int level = 0;
		PrintTree() {}

		virtual void visit(Leaf& Node) override {
			std::cout << indent(3 * level) << Node.id << "  " << Node.tok.text << " (" << Node.tok.type_to_string() << "): line " << Node.tok.line << ", column " << Node.tok.col << "\n";
		}

		/* // Non polymorphic version:
		virtual void visit(Internal& Node) override {
			// std::cout << indent(2 * level) << Node.id << "  Node Type: " << Node.type_to_string() << ": children: " << Node.nkids << "\n";
			// std::cout << indent(3 * level) << Node.id << "  " << Node.type_to_string() << ": children: " << Node.nkids << "\n";
			std::cout << indent(3 * level) << Node.id << "  " << Node.to_string() << ": children: " << Node.nkids << "\n";

			level++;
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
			level--;
		}
		*/
		virtual void visit(Internal& Node) override {
			std::cout << indent(3 * level) << Node.getID() << "  " << Node.to_string() << ": children: " << Node.getnkids() << "\n";

			level++;
			for (AST* tree : Node.getKids())
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
			level--;
		}

		virtual void visit(Root& Node) override { visit(static_cast<Internal&>(Node)); } // To use this, we need polymorphic methods!
		/*
		virtual void visit(Root& Node) override {
			std::cout << indent(3 * level) << Node.id << "  " << Node.to_string() << ": children: " << Node.nkids << "\n";

			level++;
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
			level--;
		}
		*/

		virtual void visit(ContextAssignment& Node) override { visit(static_cast<Internal&>(Node)); }
		/*
		virtual void visit(ContextAssignment& Node) override {
			std::cout << indent(3 * level) << Node.id << "  " << Node.to_string() << ": children: " << Node.nkids << "\n";

			level++;
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
			level--;
		}
		*/

		virtual void visit(ContextSwitch& Node) override { visit(static_cast<Internal&>(Node)); }
		/*
		virtual void visit(ContextSwitch& Node) override {
			std::cout << indent(3 * level) << Node.id << "  " << Node.to_string() << ": children: " << Node.nkids << "\n";

			level++;
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
			level--;
		}
		*/

		virtual void visit(Assignment& Node) override { visit(static_cast<Internal&>(Node)); }
		/*
		virtual void visit(Assignment& Node) override {
			std::cout << indent(3 * level) << Node.id << "  " << Node.to_string() << ": children: " << Node.nkids << "\n";

			level++;
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
			level--;
		}
		*/

		virtual void visit(GlobalAssignment& Node) override { visit(static_cast<Internal&>(Node)); }
		/*
		virtual void visit(GlobalAssignment& Node) override {
			std::cout << indent(3 * level) << Node.id << "  " << Node.to_string() << ": children: " << Node.nkids << "\n";

			level++;
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
			level--;
		}
		*/

		virtual void visit(FunctionDefinition& Node) override { visit(static_cast<Internal&>(Node)); }
		/*
		virtual void visit(FunctionDefinition& Node) override {
			std::cout << indent(3 * level) << Node.id << "  " << Node.to_string() << ": children: " << Node.nkids << "\n";

			level++;
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
			level--;
		}
		*/
	};

};
