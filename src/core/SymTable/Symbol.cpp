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


VariableSymbol::VariableSymbol(SKet::yyTOKEN tok)
	: Symbol(tok.text, tok.code)
{
	line_numbers.insert(tok.line);

	switch (ttype)
	{
	case SKet::Parser::token_type::INT:  // add more literal types here later
	case SKet::Parser::token_type::FLOAT:
	case SKet::Parser::token_type::LITERAL_KET:
	case SKet::Parser::token_type::LITERAL_BRA:
		is_const = true;
		break;
	default:
		is_const = false;
	}
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
	std::string s2 = pad_str(s, " ", 50, false); // 50 should do for now
	for (int line : line_numbers)
	{
		s2 += pad_str(std::to_string(line), " ", 6, false);
	}
	return s2;
}
