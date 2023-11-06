#include "VariableSymbol.h"

// Author: Garry Morrison
// Added: 2023-10-11
// Updated: 2023-10-11


VariableSymbol::VariableSymbol(SKet::yyTOKEN tok)
	: BaseSymbol(tok.text, tok.code)
{
	line_numbers.insert(tok.line);
	is_const = false;
}

std::string VariableSymbol::to_string(int level)
{
	std::string s = indent(2 * level);
	s += pad_str(Symbol::to_string(stype), " ", 15, false); // maybe larger than 25 later?
	if (ttype != SKet::Parser::token_type::UNKNOWN)
	{
		s += "<" + getName() + ":" + SKet::yyTOKEN::to_string(ttype) + ">";
	}
	else if (type != nullptr)
	{
		s += "<" + getName() + ":" + type->getName() + ">";
	}
	else
	{
		s += getName();
	}

	if (is_const)
	{
		s += " (const) ";
	}
	std::string s2 = pad_str(s, " ", 55, false); // 50 should do for now
	for (int line : line_numbers)
	{
		s2 += pad_str(std::to_string(line), " ", 6, false);
	}
	return s2;
}

