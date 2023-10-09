// Author: Garry Morrison
// Added: 2023-10-9
// Updated: 2023-10-9

#include <iostream>
#include "Warning.h"

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
	std::cout << "Warnings:\n";  // Fill out later!
}

