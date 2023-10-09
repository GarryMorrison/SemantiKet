// Author: Garry Morrison
// Added: 2023-10-9
// Updated: 2023-10-9

#include <iostream>
#include "Error.h"

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
	std::cout << "Errors:\n";  // Fill out later!
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

