#include "UnitTest.h"
#include "../misc/misc.h"
extern SKet::Driver driver;

bool UnitTest::ParserUpdateAll(const std::string& path)  // Update the parse results for all of our tests, over-writting previous parses.
{
	std::string path_out = path + "out/";  // Is this / char platform specific?
	if (!create_directory(path_out))
	{
		std::cout << "UnitTest::ParserUpdateAll failed to create directory: " << path_out << "\n";
		return false;
	}
	std::cout << "Updating all tests ... \n";
	return ParseDirectory(path, path_out, false);
	// return true;
}

bool UnitTest::ParserUpdateNew(const std::string& path)  // Update the parse results for tests that don't have parse results.
{
	std::string path_out = path + "out/";  // Is this / char platform specific?
	if (!create_directory(path_out))
	{
		std::cout << "UnitTest::ParserUpdateNew failed to create directory: " << path_out << "\n";
		return false;
	}
	std::cout << "Updating new tests ... \n";
	return ParseDirectory(path, path_out, true);
	// return true;
}

bool UnitTest::ParserTest(const std::string& path)  // Run parse tests on all the tests, and then compare with the previous parses (also, write output to screen and log file).
{
	std::string path_out = path + "out/";  // Is this / char platform specific?
	std::string path_log = path + "log/";  // Is this / char platform specific?  // log/ or logs/ ?? Which do we prefer?
	if (!create_directory(path_out))
	{
		std::cout << "UnitTest::ParserTest failed to create directory: " << path_out << "\n";
		return false;
	}
	if (!create_directory(path_log))
	{
		std::cout << "UnitTest::ParserTest failed to create directory: " << path_log << "\n";
		return false;
	}
	std::cout << "Running all tests ... \n";
	ParseDirectory(path, path_out, false, ".test");
	std::set<std::string> test_passed;
	std::set<std::string> test_failed;
	TestDirectory(path_out, ".parsed.txt", ".test.parsed.txt", test_passed, test_failed);
	std::string report = GenerateReport(test_passed, test_failed);
	WriteLog(path_log, report);
	std::cout << report;
	return true;
}


bool UnitTest::ParseDirectory(const std::string& source, const std::string& destination, bool new_only, const std::string& prefix)
{
	if (std::filesystem::is_directory(source))
	{
		if (std::filesystem::is_directory(destination))
		{
			std::string sket_extension = ".sket";
			std::vector<std::string> test_names;
			for (const auto& entry : std::filesystem::directory_iterator(source))
			{
				if (entry.is_regular_file() && entry.path().extension() == sket_extension)
				{
					std::string test_name = entry.path().filename().stem().string();
					test_names.push_back(test_name);
					std::cout << "    " << test_name << "\n";

					std::string stem = entry.path().stem().string();
					std::string parsed_file = stem + prefix + ".parsed.txt";
					std::string dot_file = stem + prefix + ".parsed.dot";
					std::string png_file = stem + prefix + ".parsed.png";
					std::string source_file = entry.path().string();

					// Comment these out later ... when finished testing.
					std::cout << "        " << parsed_file << "\n";
					std::cout << "        " << dot_file << "\n";
					std::cout << "        " << png_file << "\n";
					std::cout << "        " << source_file << "\n";

					if (new_only && std::filesystem::exists(destination + parsed_file))
					{
						std::cout << parsed_file << " aleady exists, skipping ... \n\n";
						continue;
					}

					std::stringstream buffer;
					// Redirect std::cout to buffer
					std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());  // Should we shift the buffer redirect to outside of the loop?

					serial.reset_id();
					driver.parse_file(source_file);
					driver.tree.print();

					/*
					if (driver.parse_error)  // Implement later.
					{
						std::cout << "Parse error:\n";
						std::cout << driver.parse_error_message;
					}
					*/

					std::string text = buffer.str();
					// Restore original buffer before exiting
					std::cout.rdbuf(prevcoutbuf);

					string_to_file(destination + parsed_file, text);

					driver.tree.save_graph(destination + dot_file);
					std::string dot_command = "dot -Tpng " + destination + dot_file + " > " + destination + png_file;
					std::cout << "dot command: " << dot_command << "\n";
					std::system(dot_command.c_str());
				}
			}
			return true;
		}
		else
		{
			std::cout << "UnitTest::ParseDirectory, destination is not a directory: " << destination << "\n";
			return false;
		}
	}
	else
	{
		std::cout << "UnitTest::ParseDirectory, source is not a directory: " << source << "\n";
		return false;
	}
}

bool UnitTest::TestDirectory(const std::string& source, const std::string& ext1, const std::string& ext2, std::set<std::string>& set1, std::set<std::string>& set2)
{
	if (std::filesystem::is_directory(source))
	{
		std::set<std::string> type_ext1;  // set of filenames with type ext1
		std::set<std::string> type_ext2;  // set of filenames with type ext2

		for (const auto& entry : std::filesystem::directory_iterator(source))
		{
			if (entry.is_regular_file())
			{
				std::string path_name_string = entry.path().filename().string();
				if (path_name_string.rfind(ext1) != std::string::npos)
				{
					std::string test_name = remove_extension(path_name_string, ext1);
					type_ext1.insert(test_name);
				}
				if (path_name_string.rfind(ext2) != std::string::npos)
				{
					std::string test_name = remove_extension(path_name_string, ext2);
					type_ext2.insert(test_name);
				}
			}
		}
		std::set<std::string> common_names;  // find the intersection of type_ext1 and type_ext2.  Broken! eg, if example.parsed.txt doesn't exist. FIXME!
		std::set_intersection(type_ext1.begin(), type_ext1.end(),
			type_ext2.begin(), type_ext2.end(),
			std::inserter(common_names, common_names.begin()));
		for (const auto& name : common_names)
		{
			std::string file1 = source + name + ext1;
			std::string file2 = source + name + ext2;

			// std::cout << name << "\n";
			// std::cout << file1 << "\n";
			// std::cout << file2 << "\n";
			if (test_files_equal(file1, file2))
			{
				// std::cout << "    " << name << "  PASSED\n";
				delete_file(source + name + ".FAILED", false);
				string_to_file(source + name + ".PASSED", "");
				set1.insert(name);
			}
			else
			{
				// std::cout << "    " << name << "  FAILED\n";
				delete_file(source + name + ".PASSED", false);
				string_to_file(source + name + ".FAILED", "");
				set2.insert(name);
			}
		}
	}
	else
	{
		std::cout << "UnitTest::TestDirectory, source is not a directory: " << source << "\n";
		return false;
	}
}

std::string UnitTest::GenerateReport(const std::set<std::string>& passed_names, const std::set<std::string>& failed_names)
{
	std::string report;
	std::string date_time = getCurrentDateTimeString();
	report = "\n---------------------------------------\n";
	report += "Date time: " + date_time + "\n";
	report += "---------------------------------------\n";
	report += "Passed:\n";
	for (auto name : passed_names)
	{
		report += "    " + name + "\n";
	}
	report += "---------------------------------------\n";
	report += "Failed:\n";
	for (auto name : failed_names)
	{
		report += "    " + name + "\n";
	}
	report += "---------------------------------------\n";
	report += "Summary:\n";
	report += "    " + std::to_string(passed_names.size() + failed_names.size()) + " tests processed\n";
	report += "    " + std::to_string(passed_names.size()) + " passed\n";
	report += "    " + std::to_string(failed_names.size()) + " failed\n";
	report += "---------------------------------------\n";
	return report;
}

void UnitTest::WriteLog(const std::string& destination, const std::string& report)
{
	std::string log_file_name = "log__" + getCurrentDateTimeString("-", "__", "-") + ".txt";
	if (create_directory(destination))
	{
		string_to_file(destination + log_file_name, report);
	}
	else
	{
		std::cerr << "Failed to write to log file: " << destination + log_file_name << "\n";
	}
}
