#pragma once

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-9-28

/* // Nope. Is an error if we put these here, apparently!
#include "../AST/Leaf.h"
#include "../AST/Internal.h"
#include "../AST/Root.h"
#include "../AST/ContextAssignment.h"
#include "../AST/ContextSwitch.h"
#include "../AST/Assignment.h"
#include "../AST/GlobalAssignment.h"
#include "../AST/FunctionDefinition.h"
*/
#include "../AST/AST.h"


namespace SKet {

	class AST;
	class Leaf;
	class Internal;
	class Root;
	class ContextAssignment;
	class ContextSwitch;
	class Assignment;
	class GlobalAssignment;
	class FunctionDefinition;
	class Chunk;
	class ChunkRule;
	class LearnRule;

	class ASTVisitor {
	public:
		virtual void visit(AST&) {};
		virtual void visit(Leaf& Node) = 0;
		virtual void visit(Internal& Node) = 0;
		virtual void visit(Root& Node) = 0;
		virtual void visit(ContextAssignment& Node) = 0;
		virtual void visit(ContextSwitch& Node) = 0;
		virtual void visit(Assignment& Node) = 0;
		virtual void visit(GlobalAssignment& Node) = 0;
		virtual void visit(FunctionDefinition& Node) = 0;
		virtual void visit(Chunk& Node) = 0;
		virtual void visit(ChunkRule& Node) = 0;
		virtual void visit(LearnRule& Node) = 0;
	};

};