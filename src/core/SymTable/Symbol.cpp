// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

#include "Symbol.h"


std::string Symbol::to_string() {
	if (type) { return "<" + getName() + ":" + type->getName() + ">"; }
	return getName();
}
