#include "SymbolTable.h"

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-15

SymbolTable::SymbolTable()
{
	globalScope = new GlobalScope(); // report error if this fails? Error::MemoryAllocationFailed perhaps?
}

void SymbolTable::Print()
{
	std::cout << "\nSymbol Table:\n-------------\n";
	if (globalScope)
	{
		std::cout << globalScope->to_string() << "\n";
	}
}