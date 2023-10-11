#pragma once

// Author: Garry Morrison
// Added: 2023-9-23
// Updated: 2023-9-23

#include "token.h"

namespace SKet {

    yyTOKEN::yyTOKEN(Parser::token_type token_code, const std::string& s, int lineno, int colno)
        : code(token_code), text(s), line(lineno), col(colno)
    {
        switch (code)
        {
        case Parser::token::INT:
        {
            ival = std::stoi(text);
            break;
        }
        case Parser::token::FLOAT:
        {
            dval = std::stod(text);
            break;
        }
        case Parser::token::ID:
        {
            sval = text;
            break;
        }
        case Parser::token::STRINGLIT:
        {
            sval = unescape(text);
            // std::cout << "text: " << text << "\n";
            // std::cout << "sval: " << sval << "\n";
            break;
        }
        default:
        {
            break;
        }
        }
    }

    /*
    std::string yyTOKEN::get_token_type(Parser::token_type token_code)
    {
        int code = static_cast<int>(token_code);
        if (token_string_map.find(code) == token_string_map.end())
        {
            return "UNKNOWN";
        }
        return token_string_map[code];
    }
    */
    /*
    std::string yyTOKEN::get_token_type(Parser::token_type token_code)
    {
        if (parser_token_string_map.find(token_code) == parser_token_string_map.end())
        {
            return "UNKNOWN";
        }
        return parser_token_string_map[token_code];
    }
    */
    std::string yyTOKEN::get_token_type(Parser::token_type token_code)
    {
        auto it = parser_token_string_map.find(token_code);
        if (it == parser_token_string_map.end())
        {
            return "UNKNOWN";
        }
        return it->second;
    }

    void yyTOKEN::print()
    {

        // std::cout << "\nyytype: " << get_token_type(code) << "\n";
        // std::cout << "line: " << line << ", column: " << col << "\n";
        // std::cout << "scan: " << text << ", len: " << text.size() << "\n";

        // std::cout << format_string(token_string, pad_digits(line, num_width), pad_digits(col, num_width), pad_str_right(get_token_type(code), str_width), text);
        std::cout << format_string(token_string, pad_str(std::to_string(line), " ", num_width), pad_str(std::to_string(col), " ", num_width), pad_str_right(get_token_type(code), str_width), text);
    }

    std::string yyTOKEN::unescape(const std::string& sin)
    {
        std::string sout;
        std::string s = sin.substr(1, sin.size() - 2);
        size_t size = s.size();
        size_t pos = 0;
        while (pos < size)
        {
            char c = s[pos];
            if (c == '\\')
            {
                if (pos + 2 >= size)
                {
                    std::cout << "malformed string literal\n";  // Later swap in lex_error(), if we can.
                    return sout;
                }
                char c2 = s[pos + 1];
                switch (c2)
                {
                case 't':
                {
                    sout += "\t";
                    pos++;
                    break;
                }
                case 'n':
                {
                    sout += "\n";
                    pos++;
                    break;
                }
                default:
                {
                    std::cout << "unrecognized escape\n";  // Later swap in lex_error(), if we can. I don't know how ....
                    // Scanner::lex_error("unrecognized escape");  // We need an instance of Scanner to invoke on....
                    return sout;
                }
                }
            }
            else
            {
                sout += c;
            }
            pos++;
        }
        return sout;
    }

    /*
    std::string yyTOKEN::type_to_string()
    {
        if (parser_token_string_map.find(code) == parser_token_string_map.end())
        {
            return "UNKNOWN";
        }
        return parser_token_string_map[code];
    }
    */
    std::string yyTOKEN::type_to_string()
    {
        auto it = parser_token_string_map.find(code);
        if (it == parser_token_string_map.end())
        {
            return "UNKNOWN";
        }
        return it->second;
    }

    std::string yyTOKEN::to_string(Parser::token_type token_code)
    {
        auto it = parser_token_string_map.find(token_code);
        if (it == parser_token_string_map.end())
        {
            return "UNKNOWN";
        }
        return it->second;
    }

    const std::map<Parser::token_type, std::string> yyTOKEN::parser_token_string_map = {  // Map parser tokens to their string name
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
};