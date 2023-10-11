#include "SymbolType.h"

// Author: Garry Morrison
// Added: 2023-10-11
// Updated: 2023-10-11

std::string SymbolType::to_string(SType stype)
{
	auto it = STypeStringMap.find(stype);
	if (it != STypeStringMap.end())
	{
		return it->second;
	}
	return "Unknown";
}

const std::map<SymbolType::SType, std::string> SymbolType::STypeStringMap = {
	{ SymbolType::SType::Base, "Base"},
	{ SymbolType::SType::Variable, "Variable"},
	{ SymbolType::SType::Context, "Context"},
	{ SymbolType::SType::LearnRule, "LearnRule"},
	{ SymbolType::SType::WildcardLearnRule, "WildcardLearnRule"},
	{ SymbolType::SType::Function, "Function"}
};
