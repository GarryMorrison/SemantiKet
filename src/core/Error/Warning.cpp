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

