#include "NodeType.h"

// Author: Garry Morrison
// Added: 2023-9-26
// Updated: 2023-9-26

// namespace SKet?

NodeTypeMap::NodeTypeMap()
{
	node_map[NodeType::Leaf] = "Leaf";
	node_map[NodeType::Internal] = "Internal";
	node_map[NodeType::Root] = "Root";
	node_map[NodeType::Statements] = "Statements";
};

std::string NodeTypeMap::Name(NodeType ntype)
{
	if (node_map.find(ntype) == node_map.end())
	{
		return "UNKNOWN";
	}
	return node_map[ntype];
}
