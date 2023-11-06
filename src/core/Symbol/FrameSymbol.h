#pragma once

// Author: Garry Morrison
// Added: 2023-11-6
// Updated: 2023-11-6

#include <string>
#include <set>
#include <map>
#include <vector>
#include "../AST/AST.h"
#include "Symbol.h"
#include "BaseSymbol.h"
#include "../AST/Chunk.h"
#include "../AST/ChunkRule.h"
#include "../ScopedSymbol/ContextSymbol.h"
#include "../Rule/Rule.h"


class FrameSymbol : public BaseSymbol {
public:
	Symbol::SType stype = Symbol::SType::Frame;
	std::string name;
	ContextSymbol* parentContext = nullptr;
	std::vector<SKet::AST*> kids;
	std::set<std::string> supported_ops;
	std::set<std::string> non_terminals;
	std::set<std::string> terminals;
	std::map<std::string, Rule::RType> idRType;
	std::map<std::string, SKet::AST*> idRHS;

	// bool is_const = true;
	// std::set<int> line_numbers;

	FrameSymbol(SKet::Chunk& node, ContextSymbol* context);

	void insertRule(SKet::ChunkRule& rule);

	// void appendLine(int line) { line_numbers.insert(line); }  // do we need this method in Symbol too?
	// std::set<int> getLines() { return line_numbers; }

	std::string getName() { return name; }
	std::string to_string() override { return to_string(0); }
	std::string to_string(int level);
};