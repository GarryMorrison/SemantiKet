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
			non_terminals.insert(name);
			terminals.erase(name);
		}
	}
	if (context)
	{
		parentContext = context;
		parentContext->setNonTerminal(name);
	}
}

void FrameSymbol::insertRule(SKet::ChunkRule& rule)
{
	// unpack a rule, and insert it into the current frame
	std::vector<SKet::AST*> rule_kids = rule.getKids();
	if (rule_kids.size() != 3)
	{
		std::cout << "Error in FrameSymbol insertRule, wrong number of kids!\n"; // Add Error EType later!
		return;
	}
	if (rule_kids[0])
	{
		std::string op = rule_kids[0]->getToken().text;
		supported_ops.insert(op);
		if (parentContext)
		{
			parentContext->setSupportedOp(op);
		}
	}

}

std::string FrameSymbol::to_string(int level)
{
	std::string s;
	s = indent(2 * level) + "Frame: " + name + "\n";
	
	s += indent(2 * level + 2) + "supported-ops: " + pmp_str(supported_ops, "[", ", ", "]\n");
	s += indent(2 * level + 2) + "non-terminals: " + pmp_str(non_terminals, "|", ">, |", ">\n");
	s += indent(2 * level + 2) + "terminals: " + pmp_str(terminals, "|", ">, |", ">\n");
	
	return s;
}
