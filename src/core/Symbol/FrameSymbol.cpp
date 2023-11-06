#include "FrameSymbol.h"
#include "../misc/misc.h"

// Author: Garry Morrison
// Added: 2023-11-6
// Updated: 2023-11-6

FrameSymbol::FrameSymbol(SKet::Chunk& node, ContextSymbol* context)
{
	name = "undefined"; // In case it doesn't get defined, set a default value
	kids = node.getKids();
	if (kids.size() != 2)
	{
		std::cout << "Error in FrameSymbol constructor, wrong number of kids!\n"; // Add Error EType later!
		return;
	}
	if (kids[0])
	{
		if (kids[0]->getNType() == Node::NType::Leaf)
		{
			name = kids[0]->getToken().text;
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
	/*
	s += indent(2 * level + 6) + "supported-ops: " + pmp_str(supported_ops, "[", ", ", "]\n");
	s += indent(2 * level + 6) + "non-terminals: " + pmp_str(non_terminals, "|", ">, |", ">\n");
	s += indent(2 * level + 6) + "terminals: " + pmp_str(terminals, "|", ">, |", ">\n");
	*/
	s += "supported-ops: " + pmp_str(supported_ops, "[", ", ", "]\n");
	s += "non-terminals: " + pmp_str(non_terminals, "|", ">, |", ">\n");
	s += "terminals: " + pmp_str(terminals, "|", ">, |", ">\n");
	return s;
}
