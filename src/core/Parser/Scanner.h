#pragma once

//
// Created by Garry Morrison on 5/10/2020.
//
// Sourced from here:
// https://github.com/bingmann/flex-bison-cpp-example
// Also inspired by code here:
// https://github.com/jonathan-beard/simple_wc_example


// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define	YY_DECL						\
    SKet::Parser::token_type				\
    SKet::Scanner::lex(				\
	SKet::Parser::semantic_type* yylval,		\
	SKet::Parser::location_type* yylloc		\
    )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer SKetFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif

// #include "parser.h"
#include "parser.tab.h"
#include <map>
#include <iostream>
#include <fstream>
#include "Serial.h"
extern Serial serial;

namespace SKet {


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

        Parser::token_type code;  // Make these variables private?
        std::string text;
        int line = 1;
        int col = 1;
        int ival = 0;
        double dval = 0;
        std::string sval;

        std::map<int, std::string> token_string_map = {  // Map token integers to their string name
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
            {300, "CONTINUE"}
        };

        std::string get_token_type(Parser::token_type token_code);
        std::string type_to_string() { return get_token_type(code); };
    };


    class Tree
    {
    public:
        int id;  // type int or size_t?
        std::string sym;
        int rule = 0;
        size_t nkids;
        yyTOKEN tok;
        std::vector<Tree*> kids;

        Tree(const std::string& s) { id = serial.get_id(); sym = s; nkids = 0; }
        Tree(const std::string& s, int r, yyTOKEN t) { id = serial.get_id(); sym = s; rule = r; tok = t; nkids = 0; }
        Tree(const std::string& s, int r, std::vector<Tree*> t) { id = serial.get_id(); sym = s; rule = r; nkids = t.size(); kids = t; }

        Tree(const std::string& s, int r) { id = serial.get_id(); sym = s; rule = r; nkids = 0; }
        Tree(const std::string& s, int r, Tree* t1);
        Tree(const std::string& s, int r, Tree* t1, Tree* t2);  // We have to do this because C++ doesn't have clean variadic functions!
        Tree(const std::string& s, int r, Tree* t1, Tree* t2, Tree* t3);
        Tree(const std::string& s, int r, Tree* t1, Tree* t2, Tree* t3, Tree* t4);

        void print(int level);
        void print() { print(0); }
        void save_graph(const std::string& filename);
        void output_graph(std::ofstream& out);
        void output_leaf(std::ofstream& out);
        void output_branch(std::ofstream& out);
        std::string pretty_print_name();

    private:
        
    };


    /** Scanner is a derived class to add some extra function to the scanner
     * class. Flex itself creates a class named yyFlexLexer, which is renamed using
     * macros to ExampleFlexLexer. However we change the context of the generated
     * yylex() function to be contained within the Scanner class. This is required
     * because the yylex() defined in ExampleFlexLexer has no parameters. */
    
    class Scanner : public SKetFlexLexer
    {
    public:
        /** Create a new scanner object. The streams arg_yyin and arg_yyout default
         * to cin and cout, but that assignment is only made when initializing in
         * yylex(). */
        Scanner(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);

        /** Required for virtual functions */
        virtual ~Scanner();

        /** This is the main lexing function. It is generated by flex according to
         * the macro declaration YY_DECL above. The generated bison parser then
         * calls this virtual function to fetch new tokens. */
        virtual Parser::token_type lex(Parser::semantic_type* yylval, Parser::location_type* yylloc);

        /** Enable debug output (via arg_yyout) if compiled into the scanner. */
        void set_debug(bool b);

        // My tweaks:
        int yylineno, yycolno;
        yyTOKEN yytoken, last_token;
        Tree* yytree;
        int token_count = 0;
        void comment();
        void whitespace();
        bool newline();
        Parser::token_type semicolon(Parser::semantic_type* yylval);

        Parser::token_type scan(Parser::token_type cat);  // Deprecated!
        Parser::token_type scan(Parser::token_type cat, Parser::semantic_type* yylval);
        Parser::token_type scan_null_token(Parser::token_type cat, Parser::semantic_type* yylval);
        

        void lex_error(const std::string& m);
        void lex_error(const Parser::location_type& l, const std::string& m);

    };

};
