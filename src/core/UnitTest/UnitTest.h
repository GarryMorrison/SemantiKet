#pragma once

// #include "../../SemantiKet.h"
#include <string>
#include <set>
#include "../Parser/Driver.h"
// class SKet::Driver;
// extern SKet::Driver driver;

class UnitTest
{
public:
	bool ParserUpdateAll(const std::string& path, bool with_png = false);  // Update the parse results for all of our tests, over-writting previous parses.
	bool ParserUpdateNew(const std::string& path, bool with_png = false);  // Update the parse results for tests that don't have parse results.
	bool ParserTest(const std::string& path, bool with_png = false);  // Run parse tests on all the tests, and then compare with the previous parses (also, write output to screen and log file).

	// Implement these some time later in the project!
	// bool Core();
	// bool LibraryOperators();

private:
	bool ParseDirectory(const std::string& source, const std::string& destination, bool new_only, const std::string& prefix = "", bool with_png = false);
	bool TestDirectory(const std::string& source, const std::string& ext1, const std::string& ext2, std::set<std::string>& passed_names, std::set<std::string>& failed_names);
	std::string GenerateReport(const std::set<std::string>& passed_names, const std::set<std::string>& failed_names);
	void WriteLog(const std::string& destination, const std::string& report);
};