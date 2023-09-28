#pragma once

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

#include <iostream>
#include "../AST/Leaf.h"
#include "../AST/Internal.h"
#include "../AST/Root.h"
#include "ASTVisitor.h"
#include "../misc/misc.h"

extern NodeTypeMap node_type;

namespace SKet {

	class PrintTree : public ASTVisitor {
	public:
		int level = 0;
		PrintTree() {}

		virtual void visit(Leaf& Node) override {
			// std::cout << "PrintTree inside Leaf\n";
			std::cout << indent(2 * level) << Node.id << "  " << Node.tok.text << " (" << Node.tok.type_to_string() << "): line " << Node.tok.line << ", column " << Node.tok.col << "\n";
		}

		virtual void visit(Internal& Node) override {
			// std::cout << "PrintTree inside Internal\n";
			std::cout << indent(2 * level) << Node.id << "  Node Type: " << node_type.Name(Node.ntype) << ": children: " << Node.nkids << "\n";
			level++;
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
		}

		virtual void visit(Root& Node) override {
			// std::cout << "PrintTree inside Root\n";
			std::cout << indent(2 * level) << Node.id << "  Node Type: " << node_type.Name(Node.ntype) << ": children: " << Node.nkids << "\n";
			level++;
			for (AST* tree : Node.kids)
			{
				if (tree)
				{
					tree->accept(*this);
				}
			}
		}

	};

};
