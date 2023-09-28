#pragma once

// Author: Garry Morrison
// Added: 2023-9-26
// Updated: 2023-9-26

#include <string>
#include <map>

// namespace SKet?

enum class NodeType { Leaf, Internal, Root, Statements };

class NodeTypeMap {
private:
	std::map<NodeType, std::string> node_map;

public:
	NodeTypeMap();
	std::string Name(NodeType ntype);

};