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
#include "../AST/Chunk.h"
#include "../AST/ChunkRule.h"
#include "../AST/LearnRule.h"
#include "ASTVisitor.h"
#include "../misc/misc.h"

extern NodeTypeMap node_type;

namespace SKet {

	class PrintTree : public ASTVisitor {
	public:
		int level = 0;
		std::string s;
		PrintTree() {}
		PrintTree(int level1) { level = level1; }
		std::string to_string() { return s; } // Do I need the \n here?

		virtual void visit(Leaf& Node) override {
			// std::cout << indent(3 * level) << Node.id << "  " << Node.tok.text << " (" << Node.tok.type_to_string() << "): line " << Node.tok.line << ", column " << Node.tok.col << "\n";
			s += indent(2 * level) + std::to_string(Node.id) + "  " + Node.tok.text + " (" + Node.tok.type_to_string() + "): line " + std::to_string(Node.tok.line) + ", column " + std::to_string(Node.tok.col) + "\n";
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
			// std::cout << indent(3 * level) << Node.getID() << "  " << Node.to_string() << ": children: " << Node.getnkids() << "\n";
			s += indent(2 * level) + std::to_string(Node.getID()) + "  " + Node.to_string() + ": children: " + std::to_string(Node.getnkids()) + "\n";

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

		virtual void visit(Root& Node) override { visit(static_cast<Internal&>(Node)); } // To use this, we need polymorphic methods! Done!
		virtual void visit(ContextAssignment& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(ContextSwitch& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(Assignment& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(GlobalAssignment& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(FunctionDefinition& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(Chunk& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(ChunkRule& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(LearnRule& Node) override { visit(static_cast<Internal&>(Node)); }

	};

};
