#include "SymbolTable.h"

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-15

SymbolTable::SymbolTable()
{
	globalScope = new GlobalScope(); // report error if this fails?
}

void SymbolTable::Print()
{
	std::cout << "Symbol Table:\n-------------\n";
	if (globalScope)
	{
		std::cout << globalScope->to_string() << "\n";
	}
}