%{ /*** C/C++ Declarations ***/

#pragma warning(disable : 4996)  // Looks like we need this for it to compile ...

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include <map>

#include "src/SemantiKet.h"
#include "src/core/Parser/Driver.h"

%}

/*** yacc/bison Declarations ***/

/* Require bison 3.3 or later */
%require "3.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
 // %debug

 /* start symbol is named "start" */
%start start
// %start snazzle

    /* write out a header file containing the token defines */
%defines

    /* use newer C++ skeleton file */
%skeleton "lalr1.cc"

    /* namespace to enclose parser in */
%define api.namespace { SKet }

/* set the parser's class identifier */
// For Bison earlier than 3.3:
// %define "parser_class_name" {Parser}
// For Bison 3.3 and later:
%define api.parser.class { Parser }


/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
// Switch off for release version:
%define parse.error verbose


%union {
    int ival;
    float fval;
    char* sval;
    class Tree* treeval;
}

%token			END	     0	"end of file"
%token			EOL		"end of line"
%token <treeval> INT   257
%token <treeval> FLOAT 258
%token <treeval> ID 259
%token <sval> STRINGLIT    260
%token      SEMICOLON 261
%token <treeval> CONTEXT_KET 262
%token      OP_KET 263
%token      CHAIN_KET 264
%token      TYPE_KET 265
%token <treeval> BOOL_KET 266
%token      EQUAL 267
%token <treeval> LITERAL_KET 268
%token <treeval> LITERAL_BRA 269
%token <treeval> RULE 270
%token <treeval> PLUS 271
%token <treeval> MINUS 272
%token <treeval> DOT 273
%token <treeval> STAR 274
%token <treeval> DSTAR 275
%token <treeval> STRING_OP 276
%token <treeval> SELF_KET 277
%token <treeval> DSELF_KET 278
%token <treeval> LOGICAL_OP 279
%token      LEFT_CURLY 280
%token      RIGHT_CURLY 281
%token      COMMA 282
%token      LEFT_SQUARE 283
%token      RIGHT_SQUARE 284
%token      RANGE 285
%token      LEFT_PAREN 286
%token      RIGHT_PAREN 287
%token <treeval> EQUALITY 288
%token <treeval> COMPARISON 289


%type <treeval> start
%type <treeval> statements
%type <treeval> statement
%type <treeval> assignment
%type <treeval> learn_rule
%type <treeval> sequence
%type <treeval> infix_op1
%type <treeval> expr
%type <treeval> chain
// %type <treeval> id_or_sequence
%type <treeval> wildcard
%type <treeval> wildcard_learn_rule
%type <treeval> string_ket
%type <treeval> literal_or_self_ket
%type <treeval> chain_ket
%type <treeval> ket
%type <treeval> id2_or_chain_ket
%type <treeval> number
%type <treeval> function_def
%type <treeval> fn_params
%type <treeval> compound_fn
%type <treeval> compound_fn_params
%type <treeval> id_or_chain_ket
%type <treeval> range
// %type <treeval> op
%type <treeval> bra_ket
%type <treeval> bracket_sequence
%type <treeval> ket_or_bracket_sequence
%type <treeval> equality
%type <treeval> comparison


%{

#include <memory>
#include "src/core/Parser/Driver.h"
#include "src/core/Parser/Scanner.h"

    /* this "connects" the bison parser in the driver to the flex scanner class
     * object. it defines the yylex() function call to pull the next token from the
     * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex



%}


%%
start: statements{ $$ = new Tree("root", 1000, $1); driver.tree = *$$; } ;

statements: statement | statement statements { $$ = new Tree("statements", 1010, $1, $2); };

statement: SEMICOLON | assignment | learn_rule | wildcard_learn_rule | function_def | chain SEMICOLON ;

assignment: ID EQUAL expr SEMICOLON{ $$ = new Tree("assignment", 1020, $1, $3); };

// learn_rule: id2_or_chain_ket RULE id_or_sequence SEMICOLON { $$ = new Tree("learn rule", 1030, $1, $2, $3); };
learn_rule: id2_or_chain_ket RULE sequence SEMICOLON{ $$ = new Tree("learn rule", 1030, $1, $2, $3); };

// sequence: ket | ket infix_op1 sequence { $$ = new Tree("sequence", 1040, $1, $2, $3); }
sequence: ket_or_bracket_sequence | ket_or_bracket_sequence infix_op1 sequence { $$ = new Tree("sequence", 1040, $1, $2, $3); }
| range | equality | comparison;  // Is this the best place to put "equality" and "comparison"?

ket_or_bracket_sequence: ket | bracket_sequence;

bracket_sequence: LEFT_PAREN sequence RIGHT_PAREN{ $$ = $2; };

id2_or_chain_ket: ID ID { $$ = new Tree("rule prefix", 1080, $1, $2); }
 | ID ID LITERAL_KET { $$ = new Tree("rule prefix", 1080, $1, $2, $3); }
| ID LITERAL_KET { $$ = new Tree("rule prefix", 1080, $1, $2); };

// id_or_sequence: ID | sequence;

// wildcard_learn_rule: ID wildcard RULE id_or_sequence SEMICOLON { $$ = new Tree("wildcard learn rule", 1050, $1, $2, $3, $4); };
wildcard_learn_rule: ID wildcard RULE sequence SEMICOLON{ $$ = new Tree("wildcard learn rule", 1050, $1, $2, $3, $4); };

wildcard: DOT | STAR | DSTAR;

infix_op1: PLUS | MINUS | DOT;

expr: CONTEXT_KET | BOOL_KET | LITERAL_BRA | number | ID chain | sequence ;  // Later swap in "ID chain" with "op chain"

chain: ID 
 | ID chain { $$ = new Tree("chain", 1050, $1, $2); }
 | number | number chain { $$ = new Tree("chain", 1050, $1, $2); }
 | compound_fn | compound_fn chain { $$ = new Tree("chain", 1050, $1, $2); };

// chain: op | op chain { $$ = new Tree("chain", 1050, $1, $2); }; // why does this produce shift-reduce errors?

number: INT | FLOAT | bra_ket;

bra_ket: LITERAL_BRA LITERAL_KET{ $$ = new Tree("bra ket", 1140, $1, $2); }
 | LITERAL_BRA chain LITERAL_KET{ $$ = new Tree("bra ket", 1140, $1, $2, $3); };

// op: ID | number | compound_fn;  // why does this produce shift-reduce errors?

// string_ket: literal_or_self_ket | literal_or_self_ket STRING_OP string_ket { $$ = new Tree("string ket", 1060, $1, $2, $3); };
string_ket: id_or_chain_ket | id_or_chain_ket STRING_OP string_ket { $$ = new Tree("string ket", 1060, $1, $2, $3); };
// | ID STRING_OP id_or_chain_ket { $$ = new Tree("string ket", 1060, $1, $2, $3); };
// | ID STRING_OP ID { $$ = new Tree("string ket", 1060, $1, $2, $3); };

literal_or_self_ket: LITERAL_KET | SELF_KET | DSELF_KET;

chain_ket: literal_or_self_ket | chain literal_or_self_ket { $$ = new Tree("chain ket", 1070, $1, $2); };

id_or_chain_ket: ID | chain_ket;

ket: string_ket ;

range: id_or_chain_ket RANGE id_or_chain_ket{ $$ = new Tree("range", 1130, $1, $3); }
| id_or_chain_ket RANGE id_or_chain_ket RANGE id_or_chain_ket { $$ = new Tree("range", 1130, $1, $3, $5); };

// equality: id_or_chain_ket EQUALITY id_or_chain_ket{ $$ = new Tree("equality", 1150, $1, $2, $3); };
equality: ket_or_bracket_sequence EQUALITY ket_or_bracket_sequence { $$ = new Tree("equality", 1150, $1, $2, $3); };

comparison: id_or_chain_ket COMPARISON id_or_chain_ket{ $$ = new Tree("comparison", 1160, $1, $2, $3); };

// function_def: ID LEFT_CURLY RIGHT_CURLY RULE id_or_sequence SEMICOLON{ $$ = new Tree("function def", 1090, $1, $4, $5); }
// | ID LEFT_CURLY fn_params RIGHT_CURLY RULE id_or_sequence SEMICOLON { $$ = new Tree("function def", 1090, $1, $3, $5, $6); };
function_def: ID LEFT_CURLY RIGHT_CURLY RULE sequence SEMICOLON{ $$ = new Tree("function def", 1090, $1, $4, $5); }
| ID LEFT_CURLY fn_params RIGHT_CURLY RULE sequence SEMICOLON { $$ = new Tree("function def", 1090, $1, $3, $5, $6); };

fn_params: ID | ID COMMA fn_params { $$ = new Tree("fn params", 1100, $1, $3); };

compound_fn: ID LEFT_SQUARE compound_fn_params RIGHT_SQUARE { $$ = new Tree("compound fn", 1110, $1, $3); };

compound_fn_params: chain | chain COMMA compound_fn_params { $$ = new Tree("compound fn params", 1120, $1, $3); };


%% /*** Additional Code ***/

void SKet::Parser::error(const Parser::location_type& l, const std::string& m)
{
    driver.error(l, m);
    std::cout << "Error on token: " << driver.lexer->last_token.text;
    std::cout << ", line " << driver.lexer->last_token.line;
    std::cout << " column " << driver.lexer->last_token.col << "\n";
}
