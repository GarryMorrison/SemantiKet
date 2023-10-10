// Author: Garry Morrison
// Added: 2023-10-9
// Updated: 2023-10-9

#include <iostream>
#include "Error.h"
#include "../misc/misc.h"

void Error::AppendError(EType etype, const std::string& where)
{
	error_types.push_back(etype);
	error_locations.push_back(where);
}

size_t Error::GetErrorCount()
{
	return error_types.size();
}

void Error::PrintErrors()
{
	std::string s;
	size_t error_count = GetErrorCount();
	s = "Found " + std::to_string(error_count) + " error(s):\n";
	std::string line = pad_str("", "-", static_cast<int>(s.size()) - 1);
	s += line + "\n";
	for (size_t i = 0; i < error_count; i++)
	{
		EType etype = error_types[i];
		if (i > 0)
		{
			s += "\n";
		}
		s += pad_str(std::to_string(i+1) + ")", " ", 5, false) + "Location:    " + error_locations[i] + "\n";
		s += pad_str("", " ", 5, false) + "Type:        " + etype.Type + "\n";
		s += pad_str("", " ", 5, false) + "Name:        " + etype.Name + "\n";
		s += pad_str("", " ", 5, false) + "Message:     " + etype.Message + "\n";
		s += pad_str("", " ", 5, false) + "Description: " + etype.Description + "\n";
	}
	s += line;
	std::cout << s << "\n\n";
}

void Error::ResetErrors()
{
	error_types.clear();
	error_locations.clear();
}

const EType Error::FoundSpExpectingKet = {
		"FoundSpExpectingKet",
		"Value",
		"Found a superposition, but expecting a ket",
		""
};

const EType Error::FoundSeqExpectingSp = {
	"FoundSeqExpectingSp",
	"Value",
	"Found a sequence, but expecting a superposition",
	""
};

const EType Error::InvalidBranch = {
	"InvalidBranch",
	"misc",
	"invalid branch, we should not be here!",
	""
};


