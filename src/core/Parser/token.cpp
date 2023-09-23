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

    std::string yyTOKEN::get_token_type(Parser::token_type token_code)
    {
        int code = static_cast<int>(token_code);
        if (token_string_map.find(code) == token_string_map.end())
        {
            return "UNKNOWN";
        }
        return token_string_map[code];
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

};