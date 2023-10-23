%{ /*** C/C++ Declarations ***/

#pragma warning(disable : 4996)  // Looks like we need this for it to compile ...
// #pragma warning(disable : 4005)  // does this silence our warnings? Nope!

    // #include <stdint.h>  // Nope. That didn't help.
#include <string>
#include <memory>

// #include "src/winflexbison/FlexLexer.h"
#include "src/SemantiKet.h"
#include "src/core/Parser/Scanner.h"

int current_indentation = 0;

/* import the parser's token type into a local typedef */
typedef SKet::Parser::token token;
typedef SKet::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

     /* This disables inclusion of unistd.h, which is not available under Visual C++
      * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

    /*
    ulong get_ket_idx(char* str, yy_size_t len) { // tidy later!!
        // std::string s(str, len);
        // return ket_map.get_idx(s.substr(1, s.size() - 2));
        if (len <= 2) { return ket_map.get_idx(""); } // later swap in the value of get_idx("").
        std::string s(++str, len - 2);
        return ket_map.get_idx(s);
    }

    ulong get_op_idx(char* str, yy_size_t len) {
        std::string s(str, len);
        return ket_map.get_idx(s);

    }
    */

%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "SDBFlexLexer" */
%option prefix="SKet"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

 /* no support for include files is planned */
%option yywrap nounput

    /* enables the use of start condition stacks */
%option stack

    /* The following paragraph suffices to track locations accurately. Each time
     * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}


%%

%{
    // reset location
    yylloc->step();
%}
"/*"([^*]|"*"+[^/*])*"*"+"/" { comment(); }
"//".*\r?\n { comment(); return semicolon(yylval); }
[ \t\r\f]+ { whitespace(); }
\n { if (newline()) { return semicolon(yylval); }; }
"|context: "[a-zA-Z0-9 ]+">" { return scan(token::CONTEXT_KET, yylval); }
"|op: "[a-zA-Z!\?][a-zA-Z0-9\-\+!\?\.:]*">" { return scan(token::OP_KET, yylval); }
"|chain: "([^<|>]|"\\<"|"\\\|"|"\\>")*">" { return scan(token::CHAIN_KET, yylval); }
"|type: "[a-zA-Z]+">" { return scan(token::TYPE_KET, yylval); }
"|yes>" { return scan(token::BOOL_KET, yylval); }
"|no>" { return scan(token::BOOL_KET, yylval); }
"and" { return scan(token::LOGICAL_OP, yylval); }
"or" { return scan(token::LOGICAL_OP, yylval); }
"xor" { return scan(token::LOGICAL_OP, yylval); }
"_self" { return scan(token::SELF_KET, yylval); }
"__self" { return scan(token::DSELF_KET, yylval); }
"__self"[0-9]+ { return scan(token::DSELFK_KET, yylval); }
"_params" { return scan(token::PARAMS, yylval); }
"error" { return scan(token::ERROR, yylval); }
"_is_error" { return scan(token::IS_ERROR, yylval); }
"_error_message" { return scan(token::ERROR_MESSAGE, yylval); }
"..." { return scan(token::THREE_DOTS, yylval); }
"=>" { return scan(token::RULE, yylval); }
"+=>" { return scan(token::RULE, yylval); }
".=>" { return scan(token::RULE, yylval); }
"#=>" { return scan(token::RULE, yylval); }
"!=>" { return scan(token::RULE, yylval); }
"=" { return scan(token::EQUAL, yylval); }
"++=" { return scan(token::EQUAL_OP, yylval); }
"--=" { return scan(token::EQUAL_OP, yylval); }
"*=" { return scan(token::EQUAL_OP, yylval); }
"/=" { return scan(token::EQUAL_OP, yylval); }
"%=" { return scan(token::EQUAL_OP, yylval); }
"^=" { return scan(token::EQUAL_OP, yylval); }
"+=" { return scan(token::EQUAL_OP, yylval); }
".=" { return scan(token::EQUAL_OP, yylval); }
"+" { return scan(token::PLUS, yylval); }
"-" { return scan(token::MINUS, yylval); }
"." { return scan(token::DOT, yylval); }
"*" { return scan(token::STAR, yylval); }
"**" { return scan(token::DSTAR, yylval); }
"++" { return scan(token::DPLUS, yylval); }
"--" { return scan(token::DMINUS, yylval); }
"//" { return scan(token::DDIV, yylval); }
"^^" { return scan(token::DPOW, yylval); }
"%%" { return scan(token::DMOD, yylval); }
"/" { return scan(token::DIV, yylval); }
"%" { return scan(token::MOD, yylval); }
"_" { return scan(token::STRING_OP, yylval); }
"__" { return scan(token::STRING_OP, yylval); }
":_" { return scan(token::STRING_OP, yylval); }
"#" { return scan(token::STRING_OP, yylval); }
"{" { return scan(token::LEFT_CURLY, yylval); }
"}" { return scan(token::RIGHT_CURLY, yylval); }
"," { return scan(token::COMMA, yylval); }
"[" { return scan(token::LEFT_SQUARE, yylval); }
"]" { return scan(token::RIGHT_SQUARE, yylval); }
".." { return scan(token::RANGE, yylval); }
"(" { return scan(token::LEFT_PAREN, yylval); }
")" { return scan(token::RIGHT_PAREN, yylval); }
"(:" { return scan(token::LEFT_PAREN_COLON, yylval); }
":)" { return scan(token::RIGHT_PAREN_COLON, yylval); }
"==" { return scan(token::EQUALITY, yylval); }
"!=" { return scan(token::EQUALITY, yylval); }
">" { return scan(token::COMPARISON, yylval); }
">=" { return scan(token::COMPARISON, yylval); }
"< " { return scan(token::COMPARISON, yylval); }
"<=" { return scan(token::COMPARISON, yylval); }
"^" { return scan(token::POWER, yylval); }
"for" { return scan(token::FOR, yylval); }
"cfor" { return scan(token::CFOR, yylval); }
"sfor" { return scan(token::SFOR, yylval); }
"lfor" { return scan(token::LFOR, yylval); }
"in" { return scan(token::IN, yylval); }
":" { return scan(token::COLON, yylval); }
"end:" { return scan(token::END_COLON, yylval); }
"break" { return scan(token::BREAK, yylval); }
"continue" { return scan(token::CONTINUE, yylval); }
"global" { return scan(token::GLOBAL, yylval); }
"init" { return scan(token::INIT, yylval); }
"def" { return scan(token::DEF, yylval); }
"alias" { return scan(token::ALIAS, yylval); }
"return" { return scan(token::RETURN, yylval); }
"if" { return scan(token::IF, yylval); }
"while" { return scan(token::WHILE, yylval); }
"else:" { return scan(token::ELSE, yylval); }
[0-9]+\.[0-9]+ { return scan(token::FLOAT, yylval);  }
[0-9]+ { return scan(token::INT, yylval); }
"#"[a-zA-Z_][a-zA-Z0-9\-_]* { return scan(token::CONTEXT_ID, yylval); }
[a-zA-Z_][a-zA-Z0-9\-_]* { return scan(token::ID, yylval); }
\"[^\"]*\"     { return scan(token::STRINGLIT, yylval); }
"|"([^<|>]|"\\<"|"\\\|"|"\\>")*">" { return scan(token::LITERAL_KET, yylval); }
"<"[^ =]([^<|>]|"\\<"|"\\\|"|"\\>")*"|" { return scan(token::LITERAL_BRA, yylval); }
.  { lex_error(*yylloc, yytext); }
%% /*** Additional Code ***/
namespace SKet {

    class yyTOKEN;

    Scanner::Scanner(std::istream* in, std::ostream* out)
        : SKetFlexLexer(in, out)
    {
        yylineno = 1;
        yycolno = 1;
    }
    Scanner::~Scanner()
    {
    }
    void Scanner::set_debug(bool b)
    {
        yy_flex_debug = b;
    }

    void Scanner::comment()
    {
        if (verbose_lex)
        {
            std::cout << "\nComment: " << yytext << "\n";
        }
        
        for (int i = 0; i < yyleng; i++)
        {
            if (yytext[i] == '\n')
            {
                yylineno++;
                yycolno = 1;
            }
            else
            {
                yycolno++;
            }
        }
    }

    void Scanner::whitespace()
    {
        yycolno += yyleng;
    }

    bool Scanner::newline()
    {
        yylineno++;
        switch (last_token.code)  // Is there a smarter way to do this?
        {
        case Parser::token::INT:
        case Parser::token::FLOAT:
        case Parser::token::ID:
        case Parser::token::STRINGLIT:
        case Parser::token::LITERAL_BRA:
        case Parser::token::BOOL_KET:
        case Parser::token::LITERAL_KET:
        case Parser::token::RIGHT_SQUARE:
        case Parser::token::RIGHT_PAREN:
        case Parser::token::COLON:
        case Parser::token::RULE:
        case Parser::token::END_COLON:
        case Parser::token::SELF_KET:
        case Parser::token::DSELF_KET:
        case Parser::token::DSELFK_KET:
        case Parser::token::PARAMS:
        case Parser::token::IS_ERROR:
        case Parser::token::ERROR_MESSAGE:
            return true;
            break;
        default:
            yycolno = 1;
            return false;
        }
    }

    Parser::token_type Scanner::semicolon(Parser::semantic_type* yylval)
    {
        // yytext = ";";
        yylineno--;
        return scan_null_token(Parser::token::SEMICOLON, yylval);
    }

    Parser::token_type Scanner::scan(Parser::token_type cat)
    {
        yytoken = yyTOKEN(cat, yytext, yylineno, yycolno);
        if (cat == Parser::token::SEMICOLON)  // Is this the cleanest way to handle the semicolon injection case?
        {
            yytoken.text = ";";
            yytoken.col = yycolno;
            yylineno++;
            yycolno = 1;
        }
        else
        {
            last_token = yytoken;
            yycolno += yyleng;
        }
        yytoken.print();  // do we need an if (verbose_lex) statement here?
        token_count++;
        // yytree = new Tree("token", 0, yytoken);
        // yylval->treeval = new Tree("token", 0, yytoken);
        return cat;
    }

    Parser::token_type Scanner::scan(Parser::token_type cat, Parser::semantic_type* yylval)
    {
        switch (cat)
        {
        case Parser::token::STRINGLIT:  // strip " from string literals
        case Parser::token::LITERAL_KET: // strip | and > from kets
        case Parser::token::LITERAL_BRA: // strip < and | from bras
        case Parser::token::OP_KET: // strip | and > from op kets
        case Parser::token::BOOL_KET: // strip | and > from bool kets
        {
            std::string s1(yytext);
            std::string s2 = s1.substr(1, s1.size() - 2);
            yytoken = yyTOKEN(cat, s2, yylineno, yycolno);
            break;
        }
        default:
            yytoken = yyTOKEN(cat, yytext, yylineno, yycolno);
        }

        // yytoken = yyTOKEN(cat, yytext, yylineno, yycolno);
        if (cat == Parser::token::SEMICOLON)  // Is this the cleanest way to handle the semicolon injection case?
        {
            yytoken.text = ";";
            yytoken.col = yycolno;
            yylineno++;
            yycolno = 1;
        }
        else
        {
            last_token = yytoken;
            yycolno += yyleng;
        }
        // yytoken.print();  // eventually add a wrapper so we can switch this on and off.
        if (verbose_lex)
        {
            yytoken.print();
        }
        token_count++;
        // yylval->treeval = new Tree("token", 0, yytoken);
        yylval->treeval = new Leaf(yytoken);
        return cat;
    }

    Parser::token_type Scanner::scan_null_token(Parser::token_type cat, Parser::semantic_type* yylval)
    {
        if (cat == Parser::token::SEMICOLON)  // Is this the cleanest way to handle the semicolon injection case?
        {
            yylineno++;
            yycolno = 1;
        }
        else
        {
            yycolno += yyleng;
        }
        yylval->treeval = NULL;
        return cat;
    }

    void Scanner::lex_error(const std::string& m)
    {
        std::cerr << "\n" << ": Lex error, token: " << m << ", line: " << yylineno << ", column: " << yycolno << "\n";
        yycolno += yyleng;
    }

    void Scanner::lex_error(const Parser::location_type& l, const std::string& m)
    {
        std::cerr << "\n" << l << ": Lex error, token: " << m << ", line: " << yylineno << ", column: " << yycolno << "\n";
        yycolno += yyleng;
    }

}

/* This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */
#ifdef yylex
#undef yylex
#endif
int SKetFlexLexer::yylex()
{
    std::cerr << "We shouldn't be here, in SKetFlexLexer::yylex() !" << std::endl;
    return 0;
}
/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */
int SKetFlexLexer::yywrap()
{
    return 1;
}
