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

Rule::RType Rule::from_string(const std::string& s)
{
	if (s == "=>") { return Rule::RType::Standard; }
	if (s == "+=>") { return Rule::RType::AddLearn; }
	if (s == ".=>") { return Rule::RType::SeqLearn; }
	if (s == "#=>") { return Rule::RType::Stored; }
	if (s == "!=>") { return Rule::RType::Memoize; }
	return Rule::RType::Standard; // default to Standard if not known
}
