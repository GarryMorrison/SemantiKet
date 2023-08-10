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
		std::string path(argv[2]);
		UnitTest utest;

		if (mode == "--test-parser-update-all")  // Update the parse results for all of our tests, over-writting previous parses.
		{
			utest.ParserUpdateAll(path);
		}
		else if (mode == "--test-parser-update-new")  // Update the parse results for tests that don't have parse results.
		{
			utest.ParserUpdateNew(path);
		}
		else if (mode == "--test-parser")  // Run parse tests on all the tests, and then compare with the previous parses (also, write output to screen and log file).
		{
			utest.ParserTest(path);
		}
		else if (mode == "--test-parser-update-all-with-png")  // Update the parse results for all of our tests, over-writting previous parses.
		{
			utest.ParserUpdateAll(path, true);
		}
		else if (mode == "--test-parser-update-new-with-png")  // Update the parse results for tests that don't have parse results.
		{
			utest.ParserUpdateNew(path, true);
		}
		else if (mode == "--test-parser-with-png")  // Run parse tests on all the tests, and then compare with the previous parses (also, write output to screen and log file).
		{
			utest.ParserTest(path, true);
		}
		else
		{
			std::cout << "\nInvalid option: " << mode << "\n";
			std::cout << "Valid options:\n";
			std::cout << "    --test-parser-update-all path-to-test-files/\n";
			std::cout << "    --test-parser-update-new path-to-test-files/\n";
			std::cout << "    --test-parser path-to-test-files/\n";
			std::cout << "    --test-parser-update-all-with-png path-to-test-files/\n";
			std::cout << "    --test-parser-update-new-with-png path-to-test-files/\n";
			std::cout << "    --test-parser-with-png path-to-test-files/\n\n";
			return 1;
		}
	}

	return 0;
}
