#include "SymbolTable.h"
#include "../Error/Error.h"
#include "../Error/Warning.h"
#include "../ScopedSymbol/ContextSymbol.h"

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-28

extern Error errors;
extern Warning warnings;

SymbolTable::SymbolTable()
{
	globalScope = new GlobalScope();
	if (!globalScope)
	{
		errors.AppendError(Error::MemoryAllocationFailed, "Symbol Table constructor");
		return;
	}
	globalScope->defineContext(new ContextSymbol("#global", "global context", globalScope));
}

void SymbolTable::Print()
{
	std::cout << "\nSymbol Table:\n-------------\n";
	if (globalScope)
	{
		std::cout << globalScope->to_string() << "\n";
	}
}