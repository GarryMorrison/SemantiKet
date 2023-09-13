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
// Switch off for release version
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
%token <treeval> SEMICOLON 261
%token <treeval> CONTEXT_KET 262
%token <treeval> OP_KET 263
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
%token <treeval> END_COLON 298
%token <treeval> BREAK 299
%token <treeval> CONTINUE 300
%token      GLOBAL 301
%token      DEF 302
%token      CFOR 303
%token      SFOR 304


%type <treeval> start
%type <treeval> statements
%type <treeval> statement
%type <treeval> context_assignment
%type <treeval> context_rhs
%type <treeval> context_op
%type <treeval> context_op_type
%type <treeval> chain
%type <treeval> param_op
%type <treeval> rhs_params
%type <treeval> number
%type <treeval> qualified_context
%type <treeval> powered_op
%type <treeval> chain_seq
%type <treeval> ket_or_seq
%type <treeval> ket
%type <treeval> seq
%type <treeval> string_seq
%type <treeval> bracket_seq
%type <treeval> range_seq
%type <treeval> sp_seq
%type <treeval> seq_seq
%type <treeval> minus_string_seq
%type <treeval> assignment
%type <treeval> learn_rule
%type <treeval> rule_lhs
%type <treeval> wildcard
%type <treeval> number_or_id
%type <treeval> chain_mbrs
%type <treeval> fn_def
// %type <treeval> fn_params
%type <treeval> param_list
%type <treeval> global_assignment
%type <treeval> for_statement
%type <treeval> block_statements
%type <treeval> block_statement
%type <treeval> cfor_statement
%type <treeval> sfor_statement
%type <treeval> rule_rhs
%type <treeval> end_or_return



// %right RIGHT_PAREN POWER
// %right POWER
// %right chain  // error!
// %right LEFT_PAREN
// Nope, doesn't help our S/R issues!
// %precedence RIGHT_PAREN
// %precedence POWER

// Nope, doesn't work either!
// %precedence LITERAL_KET
// %precedence RULE

// Nope, doesn't work either!
// %nonassoc NO_RULE
// %nonassoc RULE



// This one works!
//// %precedence ID
//%precedence NO_LEFT_PAREN
//// %precedence LITERAL_KET
//%precedence LEFT_PAREN

// This one doesn't
// %precedence POWER
// %precedence SEMICOLON

// %right POWER
// %right SEMICOLON


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

statement: SEMICOLON /* seems we need this */
| context_assignment /* define context label */
// | CONTEXT_ID /* context switch */
| qualified_context
// | chain SEMICOLON /* later switch to sequence, since chain is a proper subset of sequence */
| chain_seq SEMICOLON
| assignment SEMICOLON /* shift SEMICOLON into the assignment rule instead? */
| learn_rule
| fn_def
| for_statement
| cfor_statement
| sfor_statement
;

context_assignment: CONTEXT_ID EQUAL context_rhs{ $$ = new Tree("context assignment", 1020, $1, $3); }
;

context_rhs: LITERAL_KET /* |some context> */
// | CONTEXT_ID /* #some-context */
| qualified_context
| LITERAL_KET STRING_OP context_rhs{ $$ = new Tree("context rhs", 1030, $1, $2, $3); }
| CONTEXT_ID STRING_OP context_rhs{ $$ = new Tree("context rhs", 1030, $1, $2, $3); }
;

context_op: CONTEXT_ID DOT context_op_type{ $$ = new Tree("context op", 1040, $1, $3); }
;

context_op_type: ID
| param_op
;

qualified_context: CONTEXT_ID
| CONTEXT_ID DOT CONTEXT_ID{ $$ = new Tree("qualified context", 1080, $1, $3); }
| CONTEXT_ID DOT CONTEXT_ID LEFT_SQUARE chain RIGHT_SQUARE{ $$ = new Tree("qualified context", 1080, $1, $3, $5); }
;

param_op: ID LEFT_SQUARE rhs_params RIGHT_SQUARE{ $$ = new Tree("param op", 1050, $1, $3); }
;

rhs_params: STAR
| STRINGLIT
// | chain /* later swap in sequence */
| seq
| STAR COMMA rhs_params{ $$ = new Tree("rhs params", 1060, $1, $3); }
| STRINGLIT COMMA rhs_params{ $$ = new Tree("rhs params", 1060, $1, $3); }
| seq COMMA rhs_params{ $$ = new Tree("rhs params", 1060, $1, $3); }
;

// fn_def: DEF ID fn_params RULE seq SEMICOLON{ $$ = new Tree("fn def", 1190, $2, $3, $4, $5); }
// ;

// fn_params: /* empty */ { $$ = NULL; }
// | LEFT_SQUARE RIGHT_SQUARE{ $$ = NULL; }
// | LEFT_SQUARE param_list RIGHT_SQUARE{ $$ = new Tree("fn params", 1200, $2); }
// ;

fn_def: DEF ID RULE seq SEMICOLON{ $$ = new Tree("fn def", 1190, $2, $3, $4); }
| DEF ID LEFT_SQUARE RIGHT_SQUARE RULE seq SEMICOLON{ $$ = new Tree("fn def", 1190, $2, $5, $6); }
| DEF ID LEFT_SQUARE param_list RIGHT_SQUARE RULE seq SEMICOLON{ $$ = new Tree("fn def", 1190, $2, $4, $6, $7); }

param_list: ID
| ID COMMA param_list{ $$ = new Tree("param list", 1210, $1, $3); }
;


// chain: ID %prec NO_LEFT_PAREN
// | number %prec NO_LEFT_PAREN
//// | MINUS
// | context_op %prec NO_LEFT_PAREN
// | param_op %prec NO_LEFT_PAREN
// | powered_op %prec NO_LEFT_PAREN
chain: ID
| number
| context_op
| param_op
| powered_op
| ID chain{ $$ = new Tree("chain", 1070, $1, $2); }
| number chain{ $$ = new Tree("chain", 1070, $1, $2); }
// | MINUS chain{ $$ = new Tree("chain", 1070, $1, $2); }
| context_op chain{ $$ = new Tree("chain", 1070, $1, $2); }
| param_op chain{ $$ = new Tree("chain", 1070, $1, $2); }
| powered_op chain{ $$ = new Tree("chain", 1070, $1, $2); }
;

number: INT
| FLOAT
;

number_or_id: number
| ID
;

chain_mbrs: ID
| number
| context_op
| param_op
;

// powered_op: LEFT_PAREN chain RIGHT_PAREN POWER number{ $$ = new Tree("powered op", 1090, $2, $5); } // 7 S/R conflicts
// powered_op: bracket_seq POWER number{ $$ = new Tree("powered op", 1090, $1, $3); }  // 6 S/R conflicts
// powered_op: LEFT_PAREN_COLON chain RIGHT_PAREN_COLON POWER number{ $$ = new Tree("powered op", 1090, $2, $5); } // PAREN_COLON solves the shift/reduce for now.
powered_op: LEFT_CURLY chain RIGHT_CURLY POWER number_or_id{ $$ = new Tree("powered op", 1090, $2, $5); }
| chain_mbrs POWER number_or_id{ $$ = new Tree("powered op", 1090, $1, $3); }
;

chain_seq: chain
// | chain ket_or_seq %prec NO_RULE{ $$ = new Tree("chain seq", 1100, $1, $2); } // Nope. Doesn't help.
| chain ket_or_seq { $$ = new Tree("chain seq", 1100, $1, $2); }
;

ket_or_seq: ket
// | LEFT_PAREN seq RIGHT_PAREN{ $$ = $2; } // 6 shift/reduce conflicts!
| bracket_seq // 5 shift/reduce conflicts
;

bracket_seq: LEFT_PAREN seq RIGHT_PAREN{ $$ = $2; }
;

ket: LITERAL_KET /* |some ket> */
| SELF_KET /* _self */
| DSELF_KET /* __self */
| BOOL_KET /*  |yes> | |no> */
| OP_KET /* |op: age> */
;

// seq: string_seq /* |alpha> :_ |beta> __ |gamma> _ |s> */
// seq: sp_seq
seq: seq_seq
| range_seq /* start .. end | start .. end .. step */
;

string_seq: ket_or_seq
| chain_seq
| ket_or_seq STRING_OP string_seq{ $$ = new Tree("string seq", 1110, $1, $2, $3); }
| chain_seq STRING_OP string_seq{ $$ = new Tree("string seq", 1110, $1, $2, $3); }
;

range_seq: string_seq RANGE string_seq{ $$ = new Tree("range seq", 1120, $1, $3); }
| string_seq RANGE string_seq RANGE string_seq{ $$ = new Tree("range seq", 1120, $1, $3, $5); }
;


sp_seq: minus_string_seq
| minus_string_seq PLUS sp_seq{ $$ = new Tree("superposition seq", 1130, $1, $2, $3); }
| minus_string_seq MINUS sp_seq{ $$ = new Tree("superposition seq", 1130, $1, $2, $3); }
;

minus_string_seq: string_seq
| MINUS string_seq{ $$ = new Tree("minus string seq", 1150, $1, $2); }
;

seq_seq: sp_seq
| sp_seq DOT seq_seq{ $$ = new Tree("sequence seq", 1140, $1, $3); }
;

assignment: ID EQUAL seq{ $$ = new Tree("assignment", 1160, $1, $3); } /* Add SEMICOLON here? */
;

global_assignment: GLOBAL ID EQUAL seq SEMICOLON{ $$ = new Tree("global assignment", 1220, $2, $4); }
;

// learn_rule: rule_lhs RULE seq SEMICOLON{ $$ = new Tree("learn rule", 1170, $1, $2, $3); } // Add rule_rhs when you are ready.
learn_rule: rule_lhs RULE rule_rhs SEMICOLON{ $$ = new Tree("learn rule", 1170, $1, $2, $3); }
;

rule_rhs: seq
| SEMICOLON block_statements end_or_return{ $$ = new Tree("rule rhs", 1280, $2, $3); }
;

end_or_return: END_COLON
;


/*
rule_lhs: ID ID{ $$ = new Tree("rule lhs", 1180, $1, $2); }
// | ID ket_or_seq{ $$ = new Tree("rule lhs", 1180, $1, $2); } // 6 S/R conflicts
| ID LITERAL_KET{ $$ = new Tree("rule lhs", 1180, $1, $2); } // 1 S/R conflict // fixed!
| ID bracket_seq{ $$ = new Tree("rule lhs", 1180, $1, $2); } // 1 S/R conflict // fixed!
| ID wildcard{ $$ = new Tree("rule lhs", 1180, $1, $2); }
;
*/

rule_lhs: chain_seq
| ID wildcard{ $$ = new Tree("rule lhs", 1180, $1, $2); }
;

wildcard: DOT
| STAR
| DSTAR
;

for_statement: FOR ID IN seq COLON SEMICOLON block_statements END_COLON SEMICOLON{ $$ = new Tree("for statement", 1230, $2, $4, $7); }
;

block_statements: block_statement
| block_statement block_statements{ $$ = new Tree("block statements", 1240, $1, $2); }
;

block_statement: chain_seq SEMICOLON
| global_assignment
| learn_rule
| for_statement
| cfor_statement
| sfor_statement
;


cfor_statement: CFOR ID IN seq COLON SEMICOLON block_statements END_COLON SEMICOLON{ $$ = new Tree("cfor statement", 1250, $2, $4, $7); }
;

sfor_statement: SFOR ID IN seq COLON SEMICOLON block_statements END_COLON SEMICOLON{ $$ = new Tree("sfor statement", 1260, $2, $4, $7); }
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
