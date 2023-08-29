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

/* set to IELR(1) parser: */
%define lr.type ielr

/* enable verbose output report: */
%verbose


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
// %token <sval> STRINGLIT    260
%token <treeval> STRINGLIT 260
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
%token <treeval> CONTEXT_ID 290
%token      POWER 291
%token      LEFT_PAREN_COLON 292
%token      RIGHT_PAREN_COLON 293
%token <treeval> EQUAL_OP 294
%token      FOR 295
%token      IN 296
%token      COLON 297
%token      END_COLON 298
%token <treeval> BREAK 299
%token <treeval> CONTINUE 300
%token      GLOBAL 301


%type <treeval> start
%type <treeval> statements
%type <treeval> statement
%type <treeval> context_assignment
%type <treeval> context_rhs
%type <treeval> context_op
%type <treeval> context_op_type
%type <treeval> chain



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

statements: statement 
| statement statements { $$ = new Tree("statements", 1010, $1, $2); }
;

// statement: /* empty */   // causes 2 shift-reduce and 1 reduce-reduce error!
// | context_assignment /* define context label */
// | CONTEXT_ID /* context switch */
// ;

statement: context_assignment /* define context label */
| CONTEXT_ID /* context switch */
| chain SEMICOLON /* later switch to sequence, since chain is a proper subset of sequence */  // 4 shift/reduce conflicts!
;

context_assignment: CONTEXT_ID EQUAL context_rhs{ $$ = new Tree("context assignment", 1020, $1, $3); }
;

context_rhs: LITERAL_KET /* |some context> */
| CONTEXT_ID /* #some-context */
| LITERAL_KET STRING_OP context_rhs{ $$ = new Tree("context rhs", 1030, $1, $2, $3); }
| CONTEXT_ID STRING_OP context_rhs{ $$ = new Tree("context rhs", 1030, $1, $2, $3); }
;

context_op: CONTEXT_ID DOT context_op_type{ $$ = new Tree("context op", 1040, $1, $3); }
;

context_op_type: ID
;

chain: ID
| context_op
| ID chain{ $$ = new Tree("chain", 1070, $1, $2); }
| context_op chain{ $$ = new Tree("chain", 1070, $1, $2); }
;


%% /*** Additional Code ***/

void SKet::Parser::error(const Parser::location_type& l, const std::string& m)
{
    driver.error(l, m);
    /*
    std::cout << "Error on token: " << driver.lexer->last_token.text;
    std::cout << ", line " << driver.lexer->last_token.line;
    std::cout << " column " << driver.lexer->last_token.col << "\n";
    */
    driver.parse_error_message = m;
    driver.parse_error_message += "Error on token: " + driver.lexer->last_token.text;
    driver.parse_error_message += ", line " + std::to_string(driver.lexer->last_token.line);
    driver.parse_error_message += " column " + std::to_string(driver.lexer->last_token.col) + "\n";
    std::cout << driver.parse_error_message;
    driver.parse_error = true;
}
