//
// Author: Garry Morrison
// Created: 2023/7/6
// Updated: 2023/7/6


// SemantiKet.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <filesystem>
// #include <FlexLexer.h>
#include "core/Parser/Serial.h"
// #include "core/Parser/tree.h"
#include "core/Parser/token.h"
#include "core/Parser/tree.h"
#include "core/AST/NodeType.h"
#include "core/AST/Node.h"
#include "core/AST/AST.h"
#include "core/AST/Leaf.h"
#include "core/AST/Internal.h"
#include "core/AST/Root.h"
#include "core/AST/ContextAssignment.h"
#include "core/AST/ContextSwitch.h"
#include "core/AST/Assignment.h"
#include "core/AST/GlobalAssignment.h"
#include "core/AST/FunctionDefinition.h"
#include "core/AST/Chunk.h"
#include "core/AST/ChunkRule.h"
#include "core/AST/LearnRule.h"
#include "core/ASTVisitor/ASTVisitor.h"
#include "core/ASTVisitor/PrintTree.h"
#include "core/ASTVisitor/GraphTree.h"
#include "core/Parser/Driver.h"
#include "core/Symbol/Symbol.h"
#include "core/Symbol/VariableSymbol.h"
#include "core/Symbol/FrameSymbol.h"
#include "core/Symbol/BaseSymbol.h"
// #include "core/SymTable/VariableSymbol.h"
#include "core/SymTable/SymbolTable.h"
#include "core/ASTVisitor/MakeSymbolTables.h"
// #include "core/Parser/token.h"
// #include "core/Parser/tree.h"
#include "core/misc/misc.h"
#include "core/UnitTest/UnitTest.h"
#include "core/Diff/diff.h"
#include "core/Sequence/Superposition.h"
#include "core/Error/ErrorMap.h"
#include "core/Error/Error.h"
#include "core/Error/Warning.h"

// TODO: Reference additional headers your program requires here.

