#include "Symbol.h"

// Author: Garry Morrison
// Added: 2023-10-11
// Updated: 2023-10-11

std::string Symbol::to_string(SType stype)
{
	auto it = STypeStringMap.find(stype);
	if (it != STypeStringMap.end())
	{
		return it->second;
	}
	return "Unknown";
}

const std::map<Symbol::SType, std::string> Symbol::STypeStringMap = {
	{ Symbol::SType::Base, "Base"},
	{ Symbol::SType::Variable, "Variable"},
	{ Symbol::SType::Context, "Context"},
	{ Symbol::SType::LearnRule, "LearnRule"},
	{ Symbol::SType::WildcardLearnRule, "WildcardLearnRule"},
	{ Symbol::SType::Function, "Function"}
};
