#include "UnitTest.h"
#include "../misc/misc.h"
extern SKet::Driver driver;

bool UnitTest::ParserUpdateAll(const std::string& path, bool with_png)  // Update the parse results for all of our tests, over-writting previous parses.
{
	std::string path_out = path + "out/";  // Is this / char platform specific?
	if (!create_directory(path_out))
	{
		std::cout << "UnitTest::ParserUpdateAll failed to create directory: " << path_out << "\n";
		return false;
	}
	std::cout << "Updating all tests ... \n";
	return ParseDirectory(path, path_out, false, "", with_png);
	// return true;
}

bool UnitTest::ParserUpdateNew(const std::string& path, bool with_png)  // Update the parse results for tests that don't have parse results.
{
	std::string path_out = path + "out/";  // Is this / char platform specific?
	if (!create_directory(path_out))
	{
		std::cout << "UnitTest::ParserUpdateNew failed to create directory: " << path_out << "\n";
		return false;
	}
	std::cout << "Updating new tests ... \n";
	return ParseDirectory(path, path_out, true, "", with_png);
	// return true;
}

bool UnitTest::ParserTest(const std::string& path, bool with_png)  // Run parse tests on all the tests, and then compare with the previous parses (also, write output to screen and log file).
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
	ParseDirectory(path, path_out, false, ".test", with_png);
	std::set<std::string> test_passed;
	std::set<std::string> test_failed;
	std::map<std::string, std::string> failed_messages;
	TestDirectory(path_out, ".parsed.txt", ".test.parsed.txt", test_passed, test_failed, failed_messages);
	std::string report = GenerateReport(test_passed, test_failed, failed_messages);
	WriteLog(path_log, report);
	std::cout << report;
	return true;
}


bool UnitTest::ParseDirectory(const std::string& source, const std::string& destination, bool new_only, const std::string& prefix, bool with_png)
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
					std::string error_file = stem + prefix + ".error-message.txt";
					std::string source_file = entry.path().string();

					// Comment these out later ... when finished testing.
					std::cout << "        " << parsed_file << "\n";
					std::cout << "        " << dot_file << "\n";
					std::cout << "        " << png_file << "\n";
					std::cout << "        " << error_file << "\n";
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
					// driver.tree.print();
					SKet::PrintTree Print;
					driver.ast->accept(Print);

					
					if (driver.parse_error)
					{
						// std::cout << "Parse error:\n";
						// std::cout << driver.parse_error_message;
						string_to_file(destination + error_file, driver.parse_error_message);
					}
					else
					{
						delete_file(destination + error_file, false);
					}
					

					std::string text = buffer.str();
					// Restore original buffer before exiting
					std::cout.rdbuf(prevcoutbuf);

					string_to_file(destination + parsed_file, text);

					// driver.tree.save_graph(destination + dot_file);
					SKet::GraphTree Graph;
					driver.ast->accept(Graph);
					Graph.save(destination + dot_file);

					if (with_png)
					{
						std::string dot_command = "dot -Tpng " + destination + dot_file + " > " + destination + png_file;
						std::cout << "dot command: " << dot_command << "\n";
						std::system(dot_command.c_str());
					}
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

bool UnitTest::TestDirectory(const std::string& source, const std::string& ext1, const std::string& ext2, std::set<std::string>& passed_names, std::set<std::string>& failed_names, std::map<std::string, std::string>& failed_messages)
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
					if (!has_extension(test_name))
					{
						type_ext1.insert(test_name);
					}
				}
				if (path_name_string.rfind(ext2) != std::string::npos)
				{
					std::string test_name = remove_extension(path_name_string, ext2);
					if (!has_extension(test_name))
					{
						type_ext2.insert(test_name);
					}
				}
			}
		}
		std::set<std::string> names;  // find the union of type_ext1 and type_ext2.
		std::set_union(type_ext1.begin(), type_ext1.end(),
			type_ext2.begin(), type_ext2.end(),
			std::inserter(names, names.begin()));
		for (const auto& name : names)
		{
			std::string file1 = source + name + ext1;
			std::string file2 = source + name + ext2;

			// std::cout << name << "\n";
			// std::cout << file1 << "\n";
			// std::cout << file2 << "\n";
			std::string the_diff = diff_compare_files(file1, file2);
			std::string error_message = file_to_string(source + name + ".test.error-message.txt", false);  // Somewhere we need to delete these files...
			// if (test_files_equal(file1, file2))
			if (the_diff.empty())
			{
				// std::cout << "    " << name << "  PASSED\n";
				delete_file(source + name + ".FAILED", false);
				string_to_file(source + name + ".PASSED", "");
				// delete_file(source + name + ".diff.txt", false);  // Enable later.
				if (error_message.empty())
				{
					passed_names.insert(name);
				}
				else
				{
					failed_names.insert(name);
					failed_messages[name] = error_message;
				}
			}
			else
			{
				// std::cout << "    " << name << "  FAILED\n";
				delete_file(source + name + ".PASSED", false);
				string_to_file(source + name + ".FAILED", "");
				string_to_file(source + name + ".diff.txt", the_diff);
				failed_names.insert(name);
				failed_messages[name] = the_diff;
				if (!error_message.empty())
				{
					failed_messages[name] += "\n" + error_message;
				}
			}
		}
	}
	else
	{
		std::cout << "UnitTest::TestDirectory, source is not a directory: " << source << "\n";
		return false;
	}
}

std::string UnitTest::GenerateReport(const std::set<std::string>& passed_names, const std::set<std::string>& failed_names, std::map<std::string, std::string>& failed_messages)
{
	std::string report;
	std::string date_time = getCurrentDateTimeString();
	report = "\n---------------------------------------\n";
	report += "Date time: " + date_time + "\n";
	report += "---------------------------------------\n";
	report += "Failed:\n\n";
	for (auto name : failed_names)
	{
		report += name + ":\n";
		report += "=======================================\n";
		report += failed_messages[name] + "\n";
		report += "=======================================\n";
	}
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
