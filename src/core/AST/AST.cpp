#include "AST.h"

// Author: Garry Morrison
// Added: 2023-9-28
// Updated: 2023-10-29

namespace SKet {

	void ExtractTokensFromAST(AST* currentNode, std::vector<yyTOKEN>& tokens)
	{
		if (!currentNode)
		{
			return;
		}

		if (currentNode->getNType() == Node::NType::Leaf)
		{
			tokens.push_back(currentNode->getToken());
		}

		for (AST* child : currentNode->getKids())
		{
			ExtractTokensFromAST(child, tokens);
		}
	}
};

/* // Delete later!
namespace SKet {

	void AST::print(int level)
	{
		for (int i = 0; i < level; i++)
		{
			std::cout << " ";
		}
		if (nkids == 0)
		{
			std::cout << id << "    " << tok.text << " (" << tok.type_to_string() << "): line " << tok.line << ", column " << tok.col << "\n";
		}
		else
		{
			std::cout << id << "    " << "children: " << nkids << "\n"; // fill out later!
		}
	}

};
*/