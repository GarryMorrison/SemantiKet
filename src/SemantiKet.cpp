//
// Author: Garry Morrison
// Created: 2023/7/6
// Updated: 2023/7/6


// SemantiKet.cpp : Defines the entry point for the application.
//

#include <cstdlib>
#include <filesystem>
#include "SemantiKet.h"
// Define our serial global:
Serial serial;
 
// Define our parse tree:
SKet::Tree tree("the root");

// Define our parsing driver:
SKet::Driver driver(tree);


int main(int argc, char* argv[])
{
	std::cout << "SemantiKet says hello ... " << std::endl;

	// Access command-line arguments
	for (int i = 0; i < argc; ++i) 
	{
		std::cout << "Argument " << i << ": " << argv[i] << std::endl;
	}

	std::cout << "Current path: " << std::filesystem::current_path() << std::endl;

	
	if (argc == 2)
	{
		std::cout << "----------------------------------";
		driver.parse_file(argv[1]);
		driver.tree.print();
		driver.tree.save_graph("syntax-tree.dot");
		std::system("dot -Tpng syntax-tree.dot > tree.png");  // Comment this out if you don't want it to auto generate an image of the syntax tree.
	}
	
	if (argc > 2)
	{
		std::string mode(argv[1]);
		std::string path_or_filename(argv[2]);
		std::string sket_extension = ".sket";
		std::string parsed_extension = ".parsed.txt";

		// get mode types:
		bool update_mode = mode == "--update";
		bool update_new_mode = mode == "--update-new-only";
		bool test_mode = mode == "--test";
		bool test_verbose_mode = mode == "--test-verbose";

		if (update_mode)
		{
			std::cout << "Updating tests ... \n";
			if (std::filesystem::is_directory(path_or_filename))
			{
				std::vector<std::string> test_names;
				std::cout << "found a directory\n";
				for (const auto& entry : std::filesystem::directory_iterator(path_or_filename)) 
				{
					if (entry.is_regular_file() && entry.path().extension() == sket_extension) 
					{
						// std::cout << entry.path().filename() << std::endl;
						std::string test_name = entry.path().filename().stem().string();
						test_names.push_back(test_name);
						std::cout << "  " << test_name << "\n";

						std::string stem = entry.path().stem().string();
						std::string parsed_file = stem + ".parsed.txt";
						std::string dot_file = stem + ".parsed.dot";
						std::string png_file = stem + ".parsed.png";

						std::string source_file = entry.path().string();
						std::cout << "    " << parsed_file << "\n";
						std::cout << "    " << dot_file << "\n";
						std::cout << "    " << png_file << "\n";
						std::cout << "    " << source_file << "\n";


						std::stringstream buffer;
						// Redirect std::cout to buffer
						std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

						driver.parse_file(source_file);
						driver.tree.print();

						std::string text = buffer.str();
						// Restore original buffer before exiting
						std::cout.rdbuf(prevcoutbuf);

						string_to_file(path_or_filename + parsed_file, text);

						driver.tree.save_graph(path_or_filename + dot_file);
						std::string dot_command = "dot -Tpng " + path_or_filename + dot_file + " > " + path_or_filename + png_file;
						std::cout << "dot command: " << dot_command << "\n";
						std::system(dot_command.c_str());
					}
				}
			}
			else
			{
				std::cout << "found a file\n";
			}
		}
		else if (test_mode)
		{
			std::cout << "Running tests ... \n";
			if (std::filesystem::is_directory(path_or_filename))
			{
				std::vector<std::string> test_names;
				std::vector<std::string> passed_names;
				std::vector<std::string> error_names;
				std::cout << "found a directory\n";
				int test_count = 0;

				for (const auto& entry : std::filesystem::directory_iterator(path_or_filename))
				{
					if (entry.is_regular_file() && entry.path().extension() == sket_extension)
					{
						// std::cout << entry.path().filename() << std::endl;
						std::string test_name = entry.path().filename().stem().string();
						test_names.push_back(test_name);
						std::cout << "  " << test_name << "\n";

						std::string stem = entry.path().stem().string();
						std::string parsed_file = stem + ".parsed.txt";
						std::string test_parsed_file = stem + ".test.parsed.txt";
						std::string test_dot_file = stem + ".test.parsed.dot";
						std::string test_png_file = stem + ".test.parsed.png";

						std::string source_file = entry.path().string();
						std::cout << "    " << parsed_file << "\n";
						std::cout << "    " << test_parsed_file << "\n";
						std::cout << "    " << test_dot_file << "\n";
						std::cout << "    " << test_png_file << "\n";
						std::cout << "    " << source_file << "\n";


						std::stringstream buffer;
						// Redirect std::cout to buffer
						std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

						driver.parse_file(source_file);
						driver.tree.print();

						std::string text = buffer.str();
						// Restore original buffer before exiting
						std::cout.rdbuf(prevcoutbuf);

						string_to_file(path_or_filename + test_parsed_file, text);

						driver.tree.save_graph(path_or_filename + test_dot_file);
						std::string dot_command = "dot -Tpng " + path_or_filename + test_dot_file + " > " + path_or_filename + test_png_file;
						std::cout << "dot command: " << dot_command << "\n";
						std::system(dot_command.c_str());

						test_count++;

						if (test_files_equal(path_or_filename + parsed_file, path_or_filename + test_parsed_file))
						{
							std::cout << "  " << test_count << ")  " << test_name << "  PASSED\n";
							passed_names.push_back(test_name);
						}
						else
						{
							std::cout << "  " << test_count << ")  " << test_name << "  ERROR\n";
							error_names.push_back(test_name);
						}
					}
				}
				std::string summary;
				std::string log_file_name = "log__" + getCurrentDateTimeString("-", "__", "-") + ".txt";
				std::string log_file_path_name = path_or_filename + "logs/";  //  Platform dependency here because of the / char??
				
				std::string date_time = getCurrentDateTimeString();
				summary = "---------------------------------------\n";
				summary += "Date time: " + date_time + "\n";
				summary += "---------------------------------------\n";
				summary += "Passed:\n";
				for (auto name : passed_names)
				{
					summary += "    " + name + "\n";
				}
				summary += "---------------------------------------\n";
				summary += "Failed:\n";
				for (auto name : error_names)
				{
					summary += "    " + name + "\n";
				}
				summary += "---------------------------------------\n";
				summary += "Summary:\n";
				summary += "    " + std::to_string(test_count) + " tests processed\n";
				summary += "    " + std::to_string(passed_names.size()) + " passed\n";
				summary += "    " + std::to_string(error_names.size()) + " failed\n";
				summary += "---------------------------------------\n";

				std::cout << "log file name: " + log_file_name + "\n";
				std::cout << "log file path name: " + log_file_path_name + "\n";
				
				if (create_directory(log_file_path_name))
				{
					string_to_file(log_file_path_name + log_file_name, summary);
				}
				else
				{
					std::cerr << "Failed to write to log file!\n";
				}

				std::cout << summary;
			}

		}
		else if (test_verbose_mode)
		{
			std::cout << "Running verbose tests ... \n";
		}
	}

	return 0;
}
