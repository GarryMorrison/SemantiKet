//
// Author: Garry Morrison
// Created: 2023/7/6
// Updated: 2023/7/6


// SemantiKet.cpp : Defines the entry point for the application.
//

#include <cstdlib>
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

	
	if (argc > 1)
	{
		std::cout << "----------------------------------";
		driver.parse_file(argv[1]);
		driver.tree.print();
		driver.tree.save_graph("syntax-tree.dot");
		std::system("dot -Tpng syntax-tree.dot > tree.png");  // Comment this out if you don't want it to auto generate an image of the syntax tree.
	}
	
	return 0;
}
