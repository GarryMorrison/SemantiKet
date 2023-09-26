#include "NodeType.h"

// Author: Garry Morrison
// Added: 2023-9-26
// Updated: 2023-9-26

// namespace SKet?

NodeTypeMap::NodeTypeMap()
{
	node_map[NodeType::standard] = "standard";
	node_map[NodeType::statements] = "statements";
};

std::string NodeTypeMap::Name(NodeType ntype)
{
	if (node_map.find(ntype) == node_map.end())
	{
		return "UNKNOWN";
	}
	return node_map[ntype];
}
