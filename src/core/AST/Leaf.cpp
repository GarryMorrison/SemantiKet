#include "Leaf.h"

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

namespace SKet {

	Leaf::Leaf(yyTOKEN token)
		: tok(token)
	{
		id = serial.get_id();
		ntype = NodeType::Leaf;

		/*
		std::cout << "AST Leaf constructor:\n";
		std::cout << "id: " << id << "\n";
		std::cout << "token:\n";
		tok.print();
		*/
	}

};
