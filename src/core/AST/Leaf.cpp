#include "Leaf.h"

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

namespace SKet {

	Leaf::Leaf(yyTOKEN token) // Move to header file?
		: tok(token)
	{
		id = serial.get_id();
		ntype = Node::NType::Leaf;
	}

};
