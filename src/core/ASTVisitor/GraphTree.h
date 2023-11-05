#pragma once

// Author: Garry Morrison
// Added: 2023-9-29
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
#include "ASTVisitor.h"
#include "../misc/misc.h"

extern NodeTypeMap node_type;

namespace SKet {

	class GraphTree : public ASTVisitor {
	public:
		std::string out;
		int parent_id = -1;

		GraphTree() {}
		void save(const std::string& filename)
		{
			// std::cout << filename << ":\n\n";
			// std::cout << out << "\n";

			std::ofstream output_file(filename);

			if (output_file.is_open())
			{
				output_file << "digraph {\n";
				// output_graph(output_file);
				output_file << out;
				output_file << "}\n";
				output_file.close();
			}
			else
			{
				std::cerr << "GraphTree failed to open file: " << filename << "\n";
			}
		}

		virtual void visit(Leaf& Node) override { 
			if (parent_id != -1)
			{
				out += "N" + std::to_string(parent_id) + " -> N" + std::to_string(Node.id) + ";\n";
				parent_id = -1;
			}

			out += "N" + std::to_string(Node.id) + " [shape=box style=dotted label=\" " + Node.tok.type_to_string() + " \\n ";
			out += "text = " + Node.tok.text + " \\l line = " + std::to_string(Node.tok.line) + " \\l column = " + std::to_string(Node.tok.col) + " \\l\"];\n";
		}

		/* // non polymorphic version:
		virtual void visit(Internal& Node) override { 
			if (parent_id != -1)
			{
				out += "N" + std::to_string(parent_id) + " -> N" + std::to_string(Node.id) + ";\n";
				parent_id = -1;
			}

			// out += "N" + std::to_string(Node.id) + " [shape=box label=\"" + Node.type_to_string() + "\"]; \n";
			out += "N" + std::to_string(Node.id) + " [shape=box label=\"" + Node.to_string() + "\"]; \n";
			for (AST* child : Node.kids)
			{
				if (child)
				{
					// out += "N" + std::to_string(Node.id) + " -> N" + std::to_string(child->id) + ";\n";
					parent_id = Node.id;
					child->accept(*this);
				}
			}
		}
		*/

		virtual void visit(Internal& Node) override {
			if (parent_id != -1)
			{
				out += "N" + std::to_string(parent_id) + " -> N" + std::to_string(Node.getID()) + ";\n";
				parent_id = -1;
			}

			out += "N" + std::to_string(Node.getID()) + " [shape=box label=\"" + Node.to_string() + "\"]; \n";
			for (AST* child : Node.getKids())
			{
				if (child)
				{
					parent_id = Node.getID();
					child->accept(*this);
				}
			}
		}

		virtual void visit(Root& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(ContextAssignment& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(ContextSwitch& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(Assignment& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(GlobalAssignment& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(FunctionDefinition& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(Chunk& Node) override { visit(static_cast<Internal&>(Node)); }
		virtual void visit(ChunkRule& Node) override { visit(static_cast<Internal&>(Node)); }

	};
};