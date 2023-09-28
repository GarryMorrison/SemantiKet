#include "Internal.h"

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

namespace SKet {

	Internal::Internal(AST* t1) 
	{
		id = serial.get_id();
		ntype = NodeType::Internal;
		if (t1)
		{
			kids.push_back(t1);
			nkids++;
		}
		std::cout << "AST Internal constructor:\n";
		std::cout << "id: " << id << "\n";
		std::cout << "nkids: " << nkids << "\n";
	}

};