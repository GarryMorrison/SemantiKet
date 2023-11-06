#include "FrameSymbol.h"

// Author: Garry Morrison
// Added: 2023-11-6
// Updated: 2023-11-6

FrameSymbol::FrameSymbol(SKet::Chunk& node, ContextSymbol* context)
{
	name = "undefined"; // In case it doesn't get defined, set a default value
	if (node.nkids != 2)
	{
		std::cout << "Error in FrameSymbol constructor, wrong number of kids!\n"; // Add Error EType later!
		return;
	}
	if (node.kids[0])
	{
		if (node.kids[0]->ntype == Node::NType::Leaf)
		{
			name = node.kids[0]->getToken().text;
		}
	}
	if (context)
	{
		parentContext = context;
	}
}

void FrameSymbol::insertRule(SKet::ChunkRule& rule)
{
	// unpack a rule, and insert it into the current frame
}

std::string FrameSymbol::to_string()
{
	std::string s;
	s = "Frame: " + name + "\n";
	return s;
}