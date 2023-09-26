#include "AST.h"

// Author: Garry Morrison
// Added: 2023-9-26
// Updated: 2023-9-26

namespace SKet {

	void AST::print(int level)
	{
		for (int i = 0; i < level; i++)
		{
			std::cout << " ";
		}
		if (nkids == 0)
		{
			std::cout << id << "    " << tok.text << " (" << tok.type_to_string() << "): line " << tok.line << ", column " << tok.col << "\n";
		}
		else
		{
			std::cout << id << "    " << "children: " << nkids << "\n"; // fill out later!
		}
	}

};
