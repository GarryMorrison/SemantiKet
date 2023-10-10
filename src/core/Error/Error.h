#pragma once

// Author: Garry Morrison
// Added: 2023-10-9
// Updated: 2023-10-9

#include <string>
#include <vector>

struct EType {
	std::string Name;
	std::string Type;
	std::string Message;
	std::string Description;
};


class Error {
public:
	std::vector<EType> error_types;
	std::vector<std::string> error_locations;

	void AppendError(EType etype, const std::string& where);
	size_t GetErrorCount();
	void PrintErrors();
	void ResetErrors();

	static const EType FoundSpExpectingKet;
	static const EType FoundSeqExpectingSp;

};


