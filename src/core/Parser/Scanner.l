%{ /*** C/C++ Declarations ***/

#pragma warning(disable : 4996)  // Looks like we need this for it to compile ...

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
"=>" { return scan(token::RULE, yylval); }
"+=>" { return scan(token::RULE, yylval); }
".=>" { return scan(token::RULE, yylval); }
"#=>" { return scan(token::RULE, yylval); }
"!=>" { return scan(token::RULE, yylval); }
"=" { return scan(token::EQUAL, yylval); }
"+=" { return scan(token::EQUAL_OP, yylval); }
"-=" { return scan(token::EQUAL_OP, yylval); }
"*=" { return scan(token::EQUAL_OP, yylval); }
"/=" { return scan(token::EQUAL_OP, yylval); }
"+" { return scan(token::PLUS, yylval); }
"-" { return scan(token::MINUS, yylval); }
"." { return scan(token::DOT, yylval); }
"*" { return scan(token::STAR, yylval); }
"**" { return scan(token::DSTAR, yylval); }
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
"in" { return scan(token::IN, yylval); }
":" { return scan(token::COLON, yylval); }
"end:" { return scan(token::END_COLON, yylval); }
"break" { return scan(token::BREAK, yylval); }
"continue" { return scan(token::CONTINUE, yylval); }
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
        std::cout << "\nComment: " << yytext << "\n";
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
        yytoken.print();
        token_count++;
        // yytree = new Tree("token", 0, yytoken);
        // yylval->treeval = new Tree("token", 0, yytoken);
        return cat;
    }

    Parser::token_type Scanner::scan(Parser::token_type cat, Parser::semantic_type* yylval)
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
        yytoken.print();
        token_count++;
        yylval->treeval = new Tree("token", 0, yytoken);
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
        /*
        std::cout << "\nyytype: " << get_token_type(code) << "\n";
        std::cout << "line: " << line << ", column: " << col << "\n";
        std::cout << "scan: " << text << ", len: " << text.size() << "\n";
        */
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

    void Tree::print(int level)
    {
        for (int i = 0; i < level; i++)
        {
            std::cout << "  ";
        }
        if (nkids == 0)
        {
            std::cout << id << "    " << tok.text << " (" << tok.type_to_string() << "): line " << tok.line << ", column " << tok.col << "\n";
        }
        else
        {
            std::cout << id << "    " << sym << " (" << rule << "): children: " << nkids << "\n";
            for (Tree* tree : kids)
            {
                if (tree)
                {
                    tree->print(level + 1);
                }
            }
        }
    }

    void Tree::save_graph(const std::string& filename)
    {
        std::ofstream output_file(filename);

        if (output_file.is_open())
        {
            output_file << "digraph {\n";
            output_graph(output_file);
            output_file << "}\n";
            output_file.close();
        }
        else
        {
            std::cerr << "save graph failed to open file: " << filename << "\n";
        }
    }

    void Tree::output_graph(std::ofstream& out)
    {
        if (nkids == 0)
        {
            output_leaf(out);
            return;
        }
        output_branch(out);
        for (Tree* child : kids)
        {
            if (child)
            {
                out << "N" << id << " -> N" << child->id << ";\n";
                child->output_graph(out);
            }
        }
    }

    void Tree::output_leaf(std::ofstream& out)
    {
        std::string s = tok.type_to_string();
        output_branch(out);
        out << "N" << id << " [shape=box style=dotted label=\" " << s << " \\n ";
        out << "text = " << tok.text << " \\l line = " << tok.line << " \\l column = " << tok.col << " \\l\"];\n";
    }

    void Tree::output_branch(std::ofstream& out)
    {
        out << "N" << id << " [shape=box label=\"" << pretty_print_name() << "\"]; \n";
    }

    std::string Tree::pretty_print_name()
    {
        if (tok.text.empty())
        {
            return sym + "#" + std::to_string(rule);
        }
        else
        {
            return tok.text + ":" + tok.type_to_string();
        }
    }

    Tree::Tree(const std::string& s, int r, Tree* t1) 
    { 
        id = serial.get_id(); 
        sym = s; 
        rule = r;
        nkids = 0;
        if (t1)
        {
            kids.push_back(t1);
            nkids++;
        }
    }

    Tree::Tree(const std::string& s, int r, Tree* t1, Tree* t2)
    {
        id = serial.get_id();
        sym = s;
        rule = r;
        nkids = 0;
        if (t1)
        {
            kids.push_back(t1);
            nkids++;
        }
        if (t2)
        {
            kids.push_back(t2);
            nkids++;
        }
    }

    Tree::Tree(const std::string& s, int r, Tree* t1, Tree* t2, Tree* t3)
    {
        id = serial.get_id();
        sym = s;
        rule = r;
        nkids = 0;
        if (t1)
        {
            kids.push_back(t1);
            nkids++;
        }
        if (t2)
        {
            kids.push_back(t2);
            nkids++;
        }
        if (t3)
        {
            kids.push_back(t3);
            nkids++;
        }
    }

    Tree::Tree(const std::string& s, int r, Tree* t1, Tree* t2, Tree* t3, Tree* t4)
    {
        id = serial.get_id();
        sym = s;
        rule = r;
        nkids = 0;
        if (t1)
        {
            kids.push_back(t1);
            nkids++;
        }
        if (t2)
        {
            kids.push_back(t2);
            nkids++;
        }
        if (t3)
        {
            kids.push_back(t3);
            nkids++;
        }
        if (t4)
        {
            kids.push_back(t4);
            nkids++;
        }
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
