// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

#include "Symbol.h"
#include "../misc/misc.h"

SKet::yyTOKEN sample_token; // we need a cleaner way to access token names!

/*
Symbol::Symbol(const std::string& name, Type* type, bool is_const, int line) 
{ 
	this->name = name; 
	this->type = type; 
	this->is_const = is_const; 
	this->line_numbers.push_back(line); 
}
*/

std::string Symbol::to_string() {
	std::string s;
	if (type != nullptr) 
	{ 
		s = "<" + getName() + ":" + type->getName() + ">"; 
	}
	else
	{
		s = getName();
	}
	/*
	if (is_const)
	{
		s += " (const) ";
	}
	for (int line : line_numbers)
	{
		s += pad_str(std::to_string(line), " ", 4);
	}
	*/
	return s;
}

std::string VariableSymbol::to_string()
{
	std::string s;
	if (ttype != SKet::Parser::token_type::UNKNOWN)
	{
		s = "<" + getName() + ":" + sample_token.get_token_type(ttype) + ">"; // we need a cleaner way to map to token names!!
	}
	else if (type != nullptr)
	{
		s = "<" + getName() + ":" + type->getName() + ">";
	}
	else
	{
		s = getName();
	}
	
	if (is_const)
	{
		s += " (const) ";
	}
	for (int line : line_numbers)
	{
		s += pad_str(std::to_string(line), " ", 6);
	}
	
	return s;
}
