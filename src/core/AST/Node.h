#pragma once

// Author: Garry Morrison
// Added: 2023-10-9
// Updated: 2023-10-9

#include <string>
#include <map>

class Node {
public:
	enum class NType { AST, Leaf, Internal, Root, ContextAssignment, ContextSwitch, Assignment, GlobalAssignment, FunctionDefinition };

	static const std::map<NType, std::string> NTypeStringMap;
	static std::string to_string(NType ntype);
};