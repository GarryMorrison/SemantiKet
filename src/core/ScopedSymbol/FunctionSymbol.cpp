#include "FunctionSymbol.h"
#include "../Parser/token.h"
#include "../misc/misc.h"
#include "../AST/AST.h"
#include "../ASTVisitor/PrintTree.h"
#include "../Scope/LocalScope.h"
#include "../Error/Error.h"
#include "../Error/Warning.h"

extern Error errors;
extern Warning warnings;

// Author: Garry Morrison
// Added: 2023-10-29
// Updated: 2023-10-29

FunctionSymbol::FunctionSymbol(SKet::FunctionDefinition& node) // flesh out later!
{
	scope_id = scope_serial.get_id();
	fn_rtype = Rule::RType::Standard;
	if (node.nkids > 1 && node.kids[0])
	{
		SKet::yyTOKEN token = node.kids[0]->getToken();
		
		name = token.text;
		fn_name = token.text;
	}
}

FunctionSymbol::FunctionSymbol(SKet::FunctionDefinition& node, BaseScope* scope)
{
	scope_id = scope_serial.get_id();
	fn_rtype = Rule::RType::Standard;
	if (scope)
	{
		parentScope = scope;
	}
	
	
	if (node.nkids > 1 && node.kids[0])  // get the name of the function
	{
		SKet::yyTOKEN token = node.kids[0]->getToken();

		name = token.text;
		fn_name = token.text;
	}
	
	bool syntax_error = false;
	if (node.nkids == 3 && node.kids[0] && node.kids[1] && node.kids[2]) // 0 param function, ie, a pure operator
	{
		// fn_rule_type = node.kids[1]->getToken().text;
		fn_rtype = Rule::from_string(node.kids[1]->getToken().text);
	}
	else if (node.nkids == 4 && node.kids[0] && node.kids[1] && node.kids[2] && node.kids[3])
	{
		std::vector<SKet::yyTOKEN> tokens;
		SKet::ExtractTokensFromAST(node.kids[1], tokens);
		for (auto const& token : tokens)
		{
			args.push_back(token.text);
			if (token.code == SKet::Parser::token_type::THREE_DOTS)
			{
				is_variadic = true;
				if (args.size() < tokens.size())
				{
					syntax_error = true;
					std::cout << "Variadic dots must be the last argument\n"; // leave this in place for now, remove later.
					// errors.AppendError(Error::VariadicDotsMustBeLastArgument, "FunctionSymbol constructor");
					// errors.AppendError(Error::VariadicDotsMustBeLastArgument, "FunctionSymbol constructor, line: " + std::to_string(token.line) + " column: " + std::to_string(token.col));
					errors.AppendError(Error::VariadicDotsMustBeLastArgument, "FunctionSymbol constructor", token.line, token.col);
				}
			}
		}
		
		// fn_rule_type = node.kids[2]->getToken().text;
		fn_rtype = Rule::from_string(node.kids[2]->getToken().text);
	}
	else
	{
		std::cout << "Error in FunctionSymbol constructor\n"; // Later wire in an error here.
	}
	if (syntax_error)
	{
		fn_name.append("__ERROR");
	}
	else
	{
		fn_name.append("__" + std::to_string(args.size()));
		if (is_variadic)
		{
			fn_name.append("+");
		}
	}
	if (node.kids[node.nkids - 1])
	{
		RHS = node.kids[node.nkids - 1];
	}
	addChild(new LocalScope());
}

void FunctionSymbol::addChild(BaseScope* sc)
{
	if (sc)
	{
		kids.push_back(sc);
		nkids++;
	}
}

void FunctionSymbol::define(BaseSymbol* sym)
{
	if (sym)
	{
		if (!sym->name.empty())
		{
			if (symbols.find(sym->name) == symbols.end()) // name is not in set, so insert it
			{
				symbols[sym->name] = sym;
			}
			else
			{
				std::set<int> lines = sym->getLines(); // Do more stuff here later. Eg, check types match, and so on.
				for (int line : lines)
				{
					symbols[sym->name]->appendLine(line); // use it->second->appendLine(line) instead?
				}
			}
		}
	}
}

BaseSymbol* FunctionSymbol::resolve(const std::string& name)
{
	auto it = symbols.find(name);
	if (it == symbols.end())
	{
		BaseScope* parent = getEnclosingScope(); // look in parent scope too! More complex implementation later
		if (parent != nullptr)
		{
			return parent->resolve(name);
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return it->second;
	}
}

void FunctionSymbol::defineContext(ContextSymbol* context)
{
	if (context)
	{
		if (!context->name.empty())
		{
			auto it = context_symbols.find(context->name);
			if (it == context_symbols.end())
			{
				context_symbols[context->name] = context;
			}
			else
			{
				// Error::ContextRedefinition, probably.
			}
		}
	}
}

ContextSymbol* FunctionSymbol::resolveContext(const std::string& name)
{
	if (name == "#previous")
	{
		ContextSymbol* tmp = previousContext;
		previousContext = currentContext;
		currentContext = tmp;
		return tmp;
	}
	auto it = context_symbols.find(name);
	if (it == context_symbols.end())
	{
		// Error::RefUnknownContext // wire this in!
		return nullptr;
	}
	else
	{
		ContextSymbol* tmp = it->second;
		previousContext = currentContext;
		currentContext = tmp;
		return tmp;
	}
}

std::string FunctionSymbol::to_string(int level) {  // do something better here later?
	std::string s;
	s = indent(2 * level) + std::to_string(getScopeID()) + " " + getScopeName() + " " + getFunctionName() + ":\n";
	s += indent(2 * level + 10) + "args: " + pmp_str(args, "[", ", ", "]\n");
	s += indent(2 * level + 10) + "variadic: " + bool_to_str(is_variadic) + "\n";
	// s += indent(2 * level + 10) + "function rule type: " + fn_rule_type + "\n";
	s += indent(2 * level + 10) + "function rtype: " + Rule::to_string(fn_rtype) + "\n";
	if (RHS)
	{
		s += indent(2 * level + 10) + "RHS:\n";
		SKet::PrintTree Print(level + 5);
		RHS->accept(Print);
		s += indent(2 * level + 10) + "----\n";
		s += Print.to_string();
		s += indent(2 * level + 10) + "----\n";
	}

	for (const auto& elt : symbols)
	{
		if (elt.second != nullptr)
		{
			s += indent(2 * level + 12) + elt.second->to_string() + "\n";
		}
	}
	for (const auto& elt : context_symbols)
	{
		if (elt.second != nullptr)
		{
			s += indent(2 * level + 12) + elt.second->to_string() + "\n";
		}
	}
	/*
	Scope* parent = getEnclosingScope();
	if (parent != nullptr)
	{
		s += parent->to_string(level + 1);
	}
	*/
	for (BaseScope* child : kids)
	{
		if (child)
		{
			s += child->to_string(level + 5);
		}
	}
	
	return s;
}
