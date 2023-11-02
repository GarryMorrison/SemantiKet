// Author: Garry Morrison
// Added: 2023-10-9
// Updated: 2023-10-9

#include <iostream>
#include "Error.h"
#include "../misc/misc.h"

void Error::AppendError(const EType& etype, const std::string& where)
{
	error_types.push_back(etype);
	error_locations.push_back(where);
	error_lines.push_back(-1);
	error_columns.push_back(-1);
}

void Error::AppendError(const EType& etype, const std::string& where, int line, int column)
{
	error_types.push_back(etype);
	error_locations.push_back(where);
	error_lines.push_back(line);
	error_columns.push_back(column);
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
		s += pad_str(std::to_string(i+1) + ")", " ", 5, false) + "Location:    " + error_locations[i];
		if (error_lines[i] > 0)
		{
			s += ", line: " + std::to_string(error_lines[i]);
		}
		if (error_columns[i] > 0)
		{
			s += " column: " + std::to_string(error_columns[i]);
		}
		s += "\n";
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
		"Type",
		"Found a superposition, but expecting a ket",
		""
};

const EType Error::FoundSeqExpectingSp = {
	"FoundSeqExpectingSp",
	"Type",
	"Found a sequence, but expecting a superposition",
	""
};

const EType Error::InvalidBranch = {
	"InvalidBranch",
	"misc",
	"invalid branch, we should not be here!",
	""
};

const EType Error::RefUnknownContext = {
	"RefUnknownContext",
	"Symbol",
	"attempt to reference an unknown context",
	""
};

const EType Error::RefUnknownSymbol = {
	"RefUnknownSymbol",
	"Symbol",
	"attempt to reference an unknown symbol",
	""
};

const EType Error::CantAssignToConst = {
	"CantAssignToConst",
	"Syntax",
	"attempt to assign to a constant",
	""
};

const EType Error::MemoryAllocationFailed = {
	"MemoryAllocationFailed",
	"Memory",
	"failed to allocate memory",
	""
};

const EType Error::LearnRuleOpNotID = {
	"LearnRuleOpNotID",
	"Type",
	"learn rule operator must be ID",
	""
};

const EType Error::TypeMismatch = {
	"TypeMismatch",
	"Type",
	"superpositions, density operators and bra-superpositions must be pure, not mixed",
	""
};

const EType Error::VariadicDotsMustBeLastArgument = {
	"VariadicDotsMustBeLastArgument",
	"Syntax",
	"Variadic three dots must be the last argument",
	""
};

