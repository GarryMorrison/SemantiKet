#include "Node.h"

// Author: Garry Morrison
// Added: 2023-10-9
// Updated: 2023-10-9

std::string Node::to_string(NType ntype)
{
	auto it = NTypeStringMap.find(ntype);
	if (it != NTypeStringMap.end())
	{
		return it->second;
	}
	return "Unknown";
}

const std::map<Node::NType, std::string> Node::NTypeStringMap = {
	{ Node::NType::AST, "AST"},
	{ Node::NType::Leaf, "Leaf"},
	{ Node::NType::Internal, "Internal"},
	{ Node::NType::Root, "Root"}
};

