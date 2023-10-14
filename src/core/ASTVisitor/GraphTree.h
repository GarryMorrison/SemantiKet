#pragma once

// Author: Garry Morrison
// Added: 2023-9-29
// Updated: 2023-9-29

#include <iostream>
#include "../AST/Leaf.h"
#include "../AST/Internal.h"
#include "../AST/Root.h"
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
		virtual void visit(Root& Node) override { visit(static_cast<Internal&>(Node)); }

	};
};