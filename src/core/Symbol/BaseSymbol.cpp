// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

#include "BaseSymbol.h"
#include "VariableSymbol.h"
#include "ConstantSymbol.h"
#include "KetSymbol.h"
#include "../misc/misc.h"


/*
Symbol::Symbol(const std::string& name, Type* type, bool is_const, int line) 
{ 
	this->name = name; 
	this->type = type; 
	this->is_const = is_const; 
	this->line_numbers.push_back(line); 
}
*/

BaseSymbol* BaseSymbol::Construct(SKet::yyTOKEN tok)
{
	switch (tok.code)
	{
	case SKet::Parser::token_type::INT:  // add more literal types here later.
	case SKet::Parser::token_type::FLOAT:
		return new ConstantSymbol(tok);
	case SKet::Parser::token_type::LITERAL_KET:  // add more ket types here later.
		return new KetSymbol(tok);
	// case SKet::Parser::token_type::LITERAL_BRA:  // return new BraSymbol(tok) later.
	// 	return new BraSymbol(tok);
	default:
		return new VariableSymbol(tok);
	}
}


std::string BaseSymbol::to_string() {
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



