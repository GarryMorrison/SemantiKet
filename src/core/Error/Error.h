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
	std::vector<int> error_lines;
	std::vector<int> error_columns;

	void AppendError(const EType& etype, const std::string& where);
	void AppendError(const EType& etype, const std::string& where, int line, int column);

	size_t GetErrorCount();
	void PrintErrors();
	void ResetErrors();

	static const EType FoundSpExpectingKet;
	static const EType FoundSeqExpectingSp;
	static const EType InvalidBranch;
	static const EType RefUnknownContext;
	static const EType RefUnknownSymbol;
	static const EType CantAssignToConst;
	static const EType MemoryAllocationFailed;
	static const EType LearnRuleOpNotID;
	static const EType TypeMismatch;
	static const EType VariadicDotsMustBeLastArgument;

};


