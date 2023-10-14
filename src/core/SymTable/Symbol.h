#pragma once

// Author: Garry Morrison
// Added: 2023-10-11
// Updated: 2023-10-11

#include <string>
#include <map>

class Symbol {
public:
	enum class SType { Base, Constant, Ket, Bra, Variable, Context, LearnRule, WildcardLearnRule, Function };

	static const std::map<SType, std::string> STypeStringMap;
	static std::string to_string(SType stype);
};