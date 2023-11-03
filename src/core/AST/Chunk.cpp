#include "Chunk.h"

// Author: Garry Morrison
// Added: 2023-11-3
// Updated: 2023-11-3

namespace SKet {

	Chunk::Chunk(AST* t1, AST* t2)
	{
		id = serial.get_id();
		if (t1)
		{
			kids.push_back(t1);
			nkids++;
		}
		if (t2)
		{
			kids.push_back(t2);
			nkids++;
		}
	}

};