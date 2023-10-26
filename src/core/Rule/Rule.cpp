#include "Rule.h"

// Author: Garry Morrison
// Added: 2023-10-27
// Updated: 2023-10-27

std::string Rule::to_string(RType rtype)
{
	auto it = RTypeStringMap.find(rtype);
	if (it != RTypeStringMap.end())
	{
		return it->second;
	}
	return "Unknown";
}

const std::map<Rule::RType, std::string> Rule::RTypeStringMap = {
	{Rule::RType::Standard, "Standard"},
	{Rule::RType::AddLearn, "AddLearn"},
	{Rule::RType::SeqLearn, "SeqLearn"},
	{Rule::RType::Stored, "Stored"},
	{Rule::RType::Memoize, "Memoize"}
};
