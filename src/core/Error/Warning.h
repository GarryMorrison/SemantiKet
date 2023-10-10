#pragma once

// Author: Garry Morrison
// Added: 2023-10-9
// Updated: 2023-10-9

#include <string>
#include <vector>

struct WType {
	std::string Name;
	std::string Type;
	std::string Message;
	std::string Description;
};


class Warning {
public:
	std::vector<WType> warning_types;
	std::vector<std::string> warning_locations;

	void AppendWarning(WType wtype, const std::string& where);
	size_t GetWarningCount();
	void PrintWarnings();
	void ResetWarnings();

	// Go find some warning types to add here:
	// static const WType FoundSpExpectingKet;
	// static const WType FoundSeqExpectingSp;
	static const WType SumIsZero;
	static const WType MaxIsZero;
	static const WType EmptyRange;
	static const WType ZeroRangeStep;
	static const WType ZeroIndex;
	static const WType IndexRangeError;
	static const WType FoundStringExpectingFloat;

};