#pragma once

// Author: Garry Morrison
// Added: 2023-9-23
// Updated: 2023-9-23

#include <map>
// #include "../../SemantiKet.h"  // This include causes yyTOKEN not found issues!!
#include "parser.tab.h"
#include "../misc/misc.h"
// #include "../../SemantiKet.h"

// #include "parser.tab.h"

namespace SKet {

    // class Parser;

    class yyTOKEN
    {
    public:
        yyTOKEN() {};
        yyTOKEN(Parser::token_type token_code, const std::string& s, int lineno, int colno);

        int num_width = 4;
        int str_width = 20;
        // std::string token_string = ">>>  LINE {}  COLUMN {}  TYPE {}  VALUE {}\n";
        std::string token_string = ">>>  LINE {}  COLUMN {}\t{}{}\n";

        void print();

        std::string unescape(const std::string& sin);

        Parser::token_type code = Parser::token_type::EMPTY;  // Make these variables private?
        std::string text;
        int line = -1;
        int col = -1;
        int ival = 0;
        double dval = 0;
        std::string sval;

        std::map<int, std::string> token_string_map = {  // Map token integers to their string name // Deprecated, delete eventually!
            {0, "END"},
            {257, "INT"},
            {258, "FLOAT"},
            {259, "ID"},
            {260, "STRINGLIT"},
            {261, "SEMICOLON"},
            {262, "CONTEXT_KET"},
            {263, "OP_KET"},
            {264, "CHAIN_KET"},
            {265, "TYPE_KET"},
            {266, "BOOL_KET"},
            {267, "EQUAL"},
            {268, "LITERAL_KET"},
            {269, "LITERAL_BRA"},
            {270, "RULE"},
            {271, "PLUS"},
            {272, "MINUS"},
            {273, "DOT"},
            {274, "STAR"},
            {275, "DSTAR"},
            {276, "STRING_OP"},
            {277, "SELF_KET"},
            {278, "DSELF_KET"},
            {279, "LOGICAL_OP"},
            {280, "LEFT_CURLY"},
            {281, "RIGHT_CURLY"},
            {282, "COMMA"},
            {283, "LEFT_SQUARE"},
            {284, "RIGHT_SQUARE"},
            {285, "RANGE"},
            {286, "LEFT_PAREN"},
            {287, "RIGHT_PAREN"},
            {288, "EQUALITY"},
            {289, "COMPARISON"},
            {290, "CONTEXT_ID"},
            {291, "POWER"},
            {292, "LEFT_PAREN_COLON"},
            {293, "RIGHT_PAREN_COLON"},
            {294, "EQUAL_OP"},
            {295, "FOR"},
            {296, "IN"},
            {297, "COLON"},
            {298, "END_COLON"},
            {299, "BREAK"},
            {300, "CONTINUE"},
            {301, "GLOBAL"},
            {302, "DEF"},
            {303, "CFOR"},
            {304, "SFOR"},
            {305, "RETURN"},
            {306, "DPLUS"},
            {307, "DMINUS"},
            {308, "DDIV"},
            {309, "DPOW"},
            {310, "DMOD"},
            {311, "IF"},
            {312, "WHILE"},
            {313, "ELSE"},
            {314, "INIT"},
            {315, "DSELFK_KET"},
            {316, "PARAMS"},
            {317, "THREE_DOTS"},
            {318, "LFOR"},
            {319, "DIV"},
            {320, "MOD"},
            {321, "ERROR"},
            {322, "IS_ERROR"},
            {323, "ERROR_MESSAGE"}
        };

        /*
        std::map<Parser::token_type, std::string> parser_token_string_map = {  // Map parser tokens to their string name
            {Parser::token_type::EMPTY, "EMPTY"},
            {Parser::token_type::UNKNOWN, "UNKNOWN"},
            {Parser::token_type::END, "END"},
            {Parser::token_type::INT, "INT"},
            {Parser::token_type::FLOAT, "FLOAT"},
            {Parser::token_type::ID, "ID"},
            {Parser::token_type::STRINGLIT, "STRINGLIT"},
            {Parser::token_type::SEMICOLON, "SEMICOLON"},
            {Parser::token_type::CONTEXT_KET, "CONTEXT_KET"},
            {Parser::token_type::OP_KET, "OP_KET"},
            {Parser::token_type::CHAIN_KET, "CHAIN_KET"},
            {Parser::token_type::TYPE_KET, "TYPE_KET"},
            {Parser::token_type::BOOL_KET, "BOOL_KET"},
            {Parser::token_type::EQUAL, "EQUAL"},
            {Parser::token_type::LITERAL_KET, "LITERAL_KET"},
            {Parser::token_type::LITERAL_BRA, "LITERAL_BRA"},
            {Parser::token_type::RULE, "RULE"},
            {Parser::token_type::PLUS, "PLUS"},
            {Parser::token_type::MINUS, "MINUS"},
            {Parser::token_type::DOT, "DOT"},
            {Parser::token_type::STAR, "STAR"},
            {Parser::token_type::DSTAR, "DSTAR"},
            {Parser::token_type::STRING_OP, "STRING_OP"},
            {Parser::token_type::SELF_KET, "SELF_KET"},
            {Parser::token_type::DSELF_KET, "DSELF_KET"},
            {Parser::token_type::LOGICAL_OP, "LOGICAL_OP"},
            {Parser::token_type::LEFT_CURLY, "LEFT_CURLY"},
            {Parser::token_type::RIGHT_CURLY, "RIGHT_CURLY"},
            {Parser::token_type::COMMA, "COMMA"},
            {Parser::token_type::LEFT_SQUARE, "LEFT_SQUARE"},
            {Parser::token_type::RIGHT_SQUARE, "RIGHT_SQUARE"},
            {Parser::token_type::RANGE, "RANGE"},
            {Parser::token_type::LEFT_PAREN, "LEFT_PAREN"},
            {Parser::token_type::RIGHT_PAREN, "RIGHT_PAREN"},
            {Parser::token_type::EQUALITY, "EQUALITY"},
            {Parser::token_type::COMPARISON, "COMPARISON"},
            {Parser::token_type::CONTEXT_ID, "CONTEXT_ID"},
            {Parser::token_type::POWER, "POWER"},
            {Parser::token_type::LEFT_PAREN_COLON, "LEFT_PAREN_COLON"},
            {Parser::token_type::RIGHT_PAREN_COLON, "RIGHT_PAREN_COLON"},
            {Parser::token_type::EQUAL_OP, "EQUAL_OP"},
            {Parser::token_type::FOR, "FOR"},
            {Parser::token_type::IN, "IN"},
            {Parser::token_type::COLON, "COLON"},
            {Parser::token_type::END_COLON, "END_COLON"},
            {Parser::token_type::BREAK, "BREAK"},
            {Parser::token_type::CONTINUE, "CONTINUE"},
            {Parser::token_type::GLOBAL, "GLOBAL"},
            {Parser::token_type::DEF, "DEF"},
            {Parser::token_type::CFOR, "CFOR"},
            {Parser::token_type::SFOR, "SFOR"},
            {Parser::token_type::RETURN, "RETURN"},
            {Parser::token_type::DPLUS, "DPLUS"},
            {Parser::token_type::DMINUS, "DMINUS"},
            {Parser::token_type::DDIV, "DDIV"},
            {Parser::token_type::DPOW, "DPOW"},
            {Parser::token_type::DMOD, "DMOD"},
            {Parser::token_type::IF, "IF"},
            {Parser::token_type::WHILE, "WHILE"},
            {Parser::token_type::ELSE, "ELSE"},
            {Parser::token_type::INIT, "INIT"},
            {Parser::token_type::DSELFK_KET, "DSELFK_KET"},
            {Parser::token_type::PARAMS, "PARAMS"},
            {Parser::token_type::THREE_DOTS, "THREE_DOTS"},
            {Parser::token_type::LFOR, "LFOR"},
            {Parser::token_type::DIV, "DIV"},
            {Parser::token_type::MOD, "MOD"},
            {Parser::token_type::ERROR, "ERROR"},
            {Parser::token_type::IS_ERROR, "IS_ERROR"},
            {Parser::token_type::ERROR_MESSAGE, "ERROR_MESSAGE"}
        };
        */
        static const std::map<Parser::token_type, std::string> parser_token_string_map;

        std::string get_token_type(Parser::token_type token_code);
        // std::string type_to_string() { return get_token_type(code); };
        std::string type_to_string();
        static std::string to_string(Parser::token_type token_code);
    };

};