#pragma once

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

#include <iostream>
#include "../AST/Leaf.h"
#include "../AST/Internal.h"
#include "ASTVisitor.h"

namespace SKet {

	class PrintTree : public ASTVisitor {
	public:
		PrintTree() {}

		virtual void visit(Leaf& Node) override {
			std::cout << "PrintTree inside Leaf\n";
		}

		virtual void visit(Internal& Node) override {
			std::cout << "PrintTree inside Internal\n";
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
