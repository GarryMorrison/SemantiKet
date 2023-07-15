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
		std::string extension = ".sket";
		if (mode == "--update")
		{
			std::cout << "Updating tests ... \n";
			if (std::filesystem::is_directory(path_or_filename))
			{
				std::vector<std::string> test_names;
				std::cout << "found a directory\n";
				for (const auto& entry : std::filesystem::directory_iterator(path_or_filename)) 
				{
					if (entry.is_regular_file() && entry.path().extension() == extension) 
					{
						// std::cout << entry.path().filename() << std::endl;
						std::string test_name = entry.path().filename().stem().string();
						test_names.push_back(test_name);
						std::cout << "  " << test_name << "\n";

						std::string stem = entry.path().stem().string();
						std::string parsed_file = stem + ".parsed.text";
						std::string dot_file = stem + ".parsed.dot";
						std::string png_file = stem + ".parsed.png";

						std::string source_file = entry.path().string();
						std::cout << "    " << parsed_file << "\n";
						std::cout << "    " << dot_file << "\n";
						std::cout << "    " << png_file << "\n";
						std::cout << "    " << source_file << "\n";

						driver.parse_file(source_file);
						driver.tree.print();
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
		else if (mode == "--test")
		{
			std::cout << "Running tests ... \n";
		}
		else if (mode == "--test-verbose")
		{
			std::cout << "Running verbose tests ... \n";
		}
	}

	return 0;
}
