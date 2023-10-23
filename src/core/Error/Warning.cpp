// Author: Garry Morrison
// Added: 2023-10-9
// Updated: 2023-10-9

#include <iostream>
#include "Warning.h"
#include "../misc/misc.h"

void Warning::AppendWarning(WType wtype, const std::string& where)
{
	warning_types.push_back(wtype);
	warning_locations.push_back(where);
}

size_t Warning::GetWarningCount()
{
	return warning_types.size();
}

void Warning::PrintWarnings()
{
	std::string s;
	size_t warning_count = GetWarningCount();
	s = "Found " + std::to_string(warning_count) + " warning(s):\n";
	std::string line = pad_str("", "-", static_cast<int>(s.size()) - 1);
	s += line + "\n";
	for (size_t i = 0; i < warning_count; i++)
	{
		WType wtype = warning_types[i];
		if (i > 0)
		{
			s += "\n";
		}
		s += pad_str(std::to_string(i + 1) + ")", " ", 5, false) + "Location:    " + warning_locations[i] + "\n";
		s += pad_str("", " ", 5, false) + "Type:        " + wtype.Type + "\n";
		s += pad_str("", " ", 5, false) + "Name:        " + wtype.Name + "\n";
		s += pad_str("", " ", 5, false) + "Message:     " + wtype.Message + "\n";
		s += pad_str("", " ", 5, false) + "Description: " + wtype.Description + "\n";
	}
	s += line;
	std::cout << s << "\n\n";
}

void Warning::ResetWarnings()
{
	warning_types.clear();
	warning_locations.clear();
}

const WType Warning::SumIsZero = {
	"SumIsZero",
	"misc",
	"sum is 0, can't proceed",
	""
};

const WType Warning::MaxIsZero = {
	"MaxIsZero",
	"misc",
	"max is 0, can't proceed",
	""
};

const WType Warning::EmptyRange = {
	"EmptyRange",
	"IndexError",
	"indices imply empty range",
	""
};

const WType Warning::ZeroRangeStep = {
	"ZeroRangeStep",
	"IndexError",
	"range step is 0, returning empty range",
	""
};

const WType Warning::ZeroIndex = {
	"ZeroIndex",
	"IndexError",
	"indices start at 1, not 0",
	""
};

const WType Warning::IndexRangeError = {
	"IndexRangeError",
	"IndexError",
	"index is out of range",
	""
};

const WType Warning::FoundStringExpectingFloat = {
	"FoundStringExpectingFloat",
	"Type",
	"found a string, but expecting a float",
	""
};

const WType Warning::TooManyToUnpack = {
	"TooManyToUnpack",
	"Syntax",
	"too many superpositions to unpack",
	""
};

const WType Warning::TooFewToUnpack = {
	"TooFewToUnpack",
	"Syntax",
	"too few superpositions to unpack",
	""
};