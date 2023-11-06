#include "FrameSymbol.h"
#include "../misc/misc.h"
#include "../ASTVisitor/PrintTree.h"

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
	if (rule_kids[0] && rule_kids[1] && rule_kids[2])
	{
		std::string op = rule_kids[0]->getToken().text;
		supported_ops.insert(op);
		if (parentContext)
		{
			parentContext->setSupportedOp(op);
		}
		Rule::RType rtype = Rule::from_string(rule_kids[1]->getToken().text);
		idRType[op] = rtype;
		idRHS[op] = rule_kids[2];
		if (rule_kids[2]->getNType() == Node::NType::Leaf)
		{
			std::string ket = rule_kids[2]->getToken().text;
			if (parentContext)
			{
				parentContext->setTerminal(ket);
			}
			if (non_terminals.find(ket) == non_terminals.end()) // if a rule is non-terminal, then it can't also be terminal!
			{
				terminals.insert(ket);
			}
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
	
	if (idRType.size() == idRHS.size())  // not sure why they would be different lengths, but check anyway.
	{
		for (const auto& iter : idRType)
		{
			s += indent(2 * level + 4) + iter.first + " " + Rule::to_string(iter.second) + "\n";

			s += indent(2 * level + 4) + "RHS:\n";
			SKet::PrintTree Print(level + 2);
			idRHS[iter.first]->accept(Print);
			s += indent(2 * level + 4) + "----\n";
			s += Print.to_string();
			s += indent(2 * level + 4) + "----\n";
		}
	}
	return s;
}
