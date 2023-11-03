#pragma once

// Author: Garry Morrison
// Added: 2023-10-27
// Updated: 2023-10-27

#include <string>
#include <map>

class Rule {
public:
	enum class RType { Standard, AddLearn, SeqLearn, Stored, Memoize };

	static const std::map<RType, std::string> RTypeStringMap;
	static std::string to_string(RType rtype);
	static Rule::RType from_string(const std::string& s);

};
