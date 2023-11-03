%{ /*** C/C++ Declarations ***/

#pragma warning(disable : 4996)  // Looks like we need this for it to compile ...

#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include <map>

#include "src/SemantiKet.h"
#include "src/core/Parser/Driver.h"

// try this:
// #include "token.h"

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
    // class Tree* treeval;
    class AST* treeval;
}

%token          EMPTY
%token          UNKNOWN
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
%token <treeval> POWER 291
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
%token      RETURN 305
%token <treeval> DPLUS 306
%token <treeval> DMINUS 307
%token <treeval> DDIV 308
%token <treeval> DPOW 309
%token <treeval> DMOD 310
%token <treeval> IF 311
%token <treeval> WHILE 312
%token <treeval> ELSE 313
%token <treeval> INIT 314
%token <treeval> DSELFK_KET 315
%token <treeval> PARAMS 316
%token <treeval> THREE_DOTS 317
%token <treeval> LFOR 318
%token <treeval> DIV 319
%token <treeval> MOD 320
%token <treeval> ERROR 321
%token <treeval> IS_ERROR 322
%token <treeval> ERROR_MESSAGE 323
%token           ALIAS
%token <treeval> SELF_BRA
%token <treeval> DSELF_BRA
%token <treeval> DSELFK_BRA
%token           AS


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
// %type <treeval> chain_seq
// %type <treeval> ket_or_seq
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
// %type <treeval> number_or_id
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
// %type <treeval> end_or_return
%type <treeval> return_seq
%type <treeval> arith_expr
// %type <treeval> mul_div
%type <treeval> comparison_expr
%type <treeval> if_statement
// %type <treeval> expr
%type <treeval> op_assignment
%type <treeval> global_op_assignment
%type <treeval> while_statement
%type <treeval> equality_expr
// %type <treeval> bool_expr
// %type <treeval> id_bra_ket
%type <treeval> init
%type <treeval> init_list
// %type <treeval> bra_ket
%type <treeval> lfor_statement
%type <treeval> curly_seq
%type <treeval> int_or_id
%type <treeval> error_seq
%type <treeval> context_chain
%type <treeval> star_id
%type <treeval> id_star
%type <treeval> assignment_lhs
%type <treeval> fn_alias
%type <treeval> bra
%type <treeval> for_unpack
%type <treeval> chunk
%type <treeval> chunk_rules
%type <treeval> chunk_rule



%left COMMA
%left DOT
%left STRING_OP
%left PLUS MINUS

%left DPLUS DMINUS
%left STAR DIV
%right POWER MOD


%left NO_LOGICAL_OP
%left LOGICAL_OP
%left EQUALITY


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
// start: statements{ $$ = new Internal("root", 1000, $1); /* driver.tree = *$$; */ driver.ast = $$; };
start: statements{ $$ = new Root($1); driver.ast = $$; };

statements: statement 
| statement statements { $$ = new Internal("statements", 1010, $1, $2); }
;

statement: SEMICOLON /* seems we need this */
| context_assignment /* define context label */
// | CONTEXT_ID /* context switch */
| qualified_context{ $$ = new ContextSwitch($1); }
// | chain SEMICOLON /* later switch to sequence, since chain is a proper subset of sequence */
// | chain_seq SEMICOLON
| chain SEMICOLON
| assignment
| op_assignment
| learn_rule
| chunk
| fn_def
| fn_alias
| for_statement
| cfor_statement
| sfor_statement
| lfor_statement
| if_statement
| while_statement
| init
| error_seq
;

// context_assignment: CONTEXT_ID EQUAL context_rhs{ $$ = new Internal("context assignment", 1020, $1, $3); }
// context_assignment: CONTEXT_ID EQUAL context_rhs{ $$ = new ContextAssignment($1, $3); }
context_assignment: context_chain EQUAL context_rhs{ $$ = new ContextAssignment($1, $3); }
;

// context_rhs: LITERAL_KET /* |some context> */
// // | CONTEXT_ID /* #some-context */
// | qualified_context
// | LITERAL_KET STRING_OP context_rhs{ $$ = new Internal("context rhs", 1030, $1, $2, $3); }
// | CONTEXT_ID STRING_OP context_rhs{ $$ = new Internal("context rhs", 1030, $1, $2, $3); }
// ;

context_rhs: LITERAL_KET
| qualified_context
| context_rhs STRING_OP context_rhs{ $$ = new Internal("context rhs", 1030, $1, $2, $3); }
;

// context_op: CONTEXT_ID DOT context_op_type{ $$ = new Internal("context op", 1040, $1, $3); }
context_op: context_chain DOT context_op_type{ $$ = new Internal("context op", 1040, $1, $3); }
;

context_op_type: ID
| param_op
;

/*
qualified_context: CONTEXT_ID
| CONTEXT_ID DOT CONTEXT_ID{ $$ = new Internal("qualified context", 1080, $1, $3); }
| CONTEXT_ID DOT CONTEXT_ID LEFT_SQUARE chain RIGHT_SQUARE{ $$ = new Internal("qualified context", 1080, $1, $3, $5); }
;
*/

qualified_context: context_chain
| context_chain LEFT_SQUARE chain RIGHT_SQUARE{ $$ = new Internal("qualified context", 1080, $1, $3); }
;

context_chain: CONTEXT_ID
| context_chain DOT context_chain{ $$ = new Internal("context chain", 1460, $1, $3); }
;

param_op: ID LEFT_SQUARE rhs_params RIGHT_SQUARE{ $$ = new Internal("param op", 1050, $1, $3); }
;

/*
rhs_params: STAR
| STRINGLIT
| seq
| STAR COMMA rhs_params{ $$ = new Internal("rhs params", 1060, $1, $3); }
| STRINGLIT COMMA rhs_params{ $$ = new Internal("rhs params", 1060, $1, $3); }
| seq COMMA rhs_params{ $$ = new Internal("rhs params", 1060, $1, $3); }
;
*/

rhs_params: STAR
| STRINGLIT
| seq
| rhs_params COMMA rhs_params{ $$ = new Internal("rhs params", 1060, $1, $3); }
;


// fn_def: DEF ID fn_params RULE seq SEMICOLON{ $$ = new Tree("fn def", 1190, $2, $3, $4, $5); }
// ;

// fn_params: /* empty */ { $$ = NULL; }
// | LEFT_SQUARE RIGHT_SQUARE{ $$ = NULL; }
// | LEFT_SQUARE param_list RIGHT_SQUARE{ $$ = new Tree("fn params", 1200, $2); }
// ;

/*
fn_def: DEF ID RULE seq SEMICOLON{ $$ = new Tree("fn def", 1190, $2, $3, $4); }
| DEF ID LEFT_SQUARE RIGHT_SQUARE RULE seq SEMICOLON{ $$ = new Tree("fn def", 1190, $2, $5, $6); }
| DEF ID LEFT_SQUARE param_list RIGHT_SQUARE RULE seq SEMICOLON{ $$ = new Tree("fn def", 1190, $2, $4, $6, $7); }
;
*/

/*
fn_def: DEF ID RULE rule_rhs SEMICOLON{ $$ = new Internal("fn def", 1190, $2, $3, $4); }
| DEF ID LEFT_SQUARE RIGHT_SQUARE RULE rule_rhs SEMICOLON{ $$ = new Internal("fn def", 1190, $2, $5, $6); }
| DEF ID LEFT_SQUARE param_list RIGHT_SQUARE RULE rule_rhs SEMICOLON{ $$ = new Internal("fn def", 1190, $2, $4, $6, $7); }
;
*/
fn_def: DEF ID RULE rule_rhs SEMICOLON{ $$ = new FunctionDefinition($2, $3, $4); }
| DEF ID LEFT_SQUARE RIGHT_SQUARE RULE rule_rhs SEMICOLON{ $$ = new FunctionDefinition($2, $5, $6); }
| DEF ID LEFT_SQUARE param_list RIGHT_SQUARE RULE rule_rhs SEMICOLON{ $$ = new FunctionDefinition($2, $4, $6, $7); }
;

// more rules later!
fn_alias: ALIAS ID LEFT_SQUARE param_list RIGHT_SQUARE EQUAL context_chain DOT param_op{ $$ = new Internal("function alias", 1490, $2, $4, $7, $9); }
;

/*
param_list: ID
| ID COMMA param_list{ $$ = new Internal("param list", 1210, $1, $3); }
| STAR
| STAR COMMA param_list{ $$ = new Internal("param list", 1210, $1, $3); }
| THREE_DOTS
| THREE_DOTS COMMA param_list{ $$ = new Internal("param list", 1210, $1, $3); }
;
*/

param_list: ID
| STAR
| THREE_DOTS
| param_list COMMA param_list{ $$ = new Internal("param list", 1210, $1, $3); }
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
// | bra_ket
| bra
| ket
| curly_seq
| bracket_seq
| ID chain{ $$ = new Internal("chain", 1070, $1, $2); }
| number chain{ $$ = new Internal("chain", 1070, $1, $2); }
// | MINUS chain{ $$ = new Tree("chain", 1070, $1, $2); }
| context_op chain{ $$ = new Internal("chain", 1070, $1, $2); }
| param_op chain{ $$ = new Internal("chain", 1070, $1, $2); }
| powered_op chain{ $$ = new Internal("chain", 1070, $1, $2); }
// | bra_ket chain{ $$ = new Internal("chain", 1070, $1, $2); }
| bra chain{ $$ = new Internal("chain", 1070, $1, $2); }
| ket chain{ $$ = new Internal("chain", 1070, $1, $2); }
| curly_seq chain{ $$ = new Internal("chain", 1070, $1, $2); }
| bracket_seq chain{ $$ = new Internal("chain", 1070, $1, $2); }
;


number: INT
| FLOAT
;

/*
number_or_id: number
| ID
;
*/

int_or_id: INT
| ID
;

chain_mbrs: ID
| number
| context_op
| param_op
// | bra_ket
| curly_seq
| bracket_seq
;


// powered_op: LEFT_PAREN chain RIGHT_PAREN POWER number{ $$ = new Tree("powered op", 1090, $2, $5); } // 7 S/R conflicts
// powered_op: bracket_seq POWER number{ $$ = new Tree("powered op", 1090, $1, $3); }  // 6 S/R conflicts
// powered_op: LEFT_PAREN_COLON chain RIGHT_PAREN_COLON POWER number{ $$ = new Tree("powered op", 1090, $2, $5); } // PAREN_COLON solves the shift/reduce for now.
/*
powered_op: LEFT_CURLY chain RIGHT_CURLY POWER number_or_id{ $$ = new Tree("powered op", 1090, $2, $5); }
| chain_mbrs POWER number_or_id{ $$ = new Tree("powered op", 1090, $1, $3); }
;
*/
 // now redundant in grammar: // Nope! It isn't!
// powered_op: chain_mbrs DPOW number_or_id{ $$ = new Tree("powered op", 1090, $1, $3); }
powered_op: chain_mbrs DPOW int_or_id{ $$ = new Internal("powered op", 1090, $1, $3); }
;


curly_seq: LEFT_CURLY seq RIGHT_CURLY{ $$ = new Internal("curly seq", 1430, $2); }
;

// chain_seq: chain
// | chain ket_or_seq %prec NO_RULE{ $$ = new Tree("chain seq", 1100, $1, $2); } // Nope. Doesn't help.
// | chain ket_or_seq { $$ = new Tree("chain seq", 1100, $1, $2); }
// | chain ket{ $$ = new Internal("chain ket", 1100, $1, $2); } // redundant now that ket is a chain member
// ;


/*
ket_or_seq: ket
// | bracket_seq  // deprecated. Now in chain. // is this still needed anywhere?
;
*/

bracket_seq: LEFT_PAREN seq RIGHT_PAREN{ $$ = $2; } // Add Internal("bracket seq"...) ?
;


ket: LITERAL_KET /* |some ket> */
| SELF_KET /* _self */
| DSELF_KET /* __self */
| BOOL_KET /*  |yes> | |no> */
| OP_KET /* |op: age> */
| DSELFK_KET /* __self0 | __self1 | ... */
| PARAMS /* _params */
| IS_ERROR /* _is_error */
| ERROR_MESSAGE /* _error_message */
;

bra: LITERAL_BRA
| SELF_BRA
| DSELF_BRA
| DSELFK_BRA
;

// seq: string_seq /* |alpha> :_ |beta> __ |gamma> _ |s> */
// seq: sp_seq
seq: seq_seq
| range_seq /* start .. end | start .. end .. step */
// | arith_expr /* 3 ++ 5 ** 7 ^^ 2 */
| equality_expr  // 1 S/R conflict
;

/*
string_seq: ket_or_seq
| chain_seq
| ket_or_seq STRING_OP string_seq{ $$ = new Internal("string seq", 1110, $1, $2, $3); }
| chain_seq STRING_OP string_seq{ $$ = new Internal("string seq", 1110, $1, $2, $3); }
;
*/
// string_seq: ket_or_seq  // redundant!
// | chain_seq // redundant!
string_seq: chain
| string_seq STRING_OP string_seq{ $$ = new Internal("string seq", 1110, $1, $2, $3); }
;


/*
range_seq: string_seq RANGE string_seq{ $$ = new Tree("range seq", 1120, $1, $3); }
| string_seq RANGE string_seq RANGE string_seq{ $$ = new Tree("range seq", 1120, $1, $3, $5); }
;
*/

range_seq: arith_expr RANGE arith_expr{ $$ = new Internal("range seq", 1120, $1, $3); }
| arith_expr RANGE arith_expr RANGE arith_expr{ $$ = new Internal("range seq", 1120, $1, $3, $5); }
| arith_expr THREE_DOTS arith_expr{ $$ = new Internal("srange seq", 1125, $1, $3); }
| arith_expr THREE_DOTS arith_expr THREE_DOTS arith_expr{ $$ = new Internal("srange seq", 1125, $1, $3, $5); }
;

comparison_expr: arith_expr COMPARISON arith_expr{ $$ = new Internal("comparison", 1320, $1, $2, $3); }
;

arith_expr: arith_expr DPLUS arith_expr{ $$ = new Internal("arithmetic", 1300, $1, $2, $3); }
| arith_expr DMINUS arith_expr{ $$ = new Internal("arithmetic", 1300, $1, $2, $3); }
| arith_expr STAR arith_expr{ $$ = new Internal("arithmetic", 1300, $1, $2, $3); }
| arith_expr DIV arith_expr{ $$ = new Internal("arithmetic", 1300, $1, $2, $3); }
| arith_expr POWER arith_expr{ $$ = new Internal("arithmetic", 1300, $1, $2, $3); }
| arith_expr MOD arith_expr{ $$ = new Internal("arithmetic", 1300, $1, $2, $3); }
// | LEFT_PAREN arith_expr RIGHT_PAREN{ $$ = $2; } // 1 S/R conflict // I think our grammar already handles this case!
| string_seq
;


/*
arith_expr: mul_div
| mul_div DPLUS arith_expr{ $$ = new Tree("arith expr", 1300, $1, $2, $3); }
| mul_div DMINUS arith_expr{ $$ = new Tree("arith expr", 1300, $1, $2, $3); }
;

mul_div: string_seq
| string_seq DSTAR mul_div{ $$ = new Tree("mul div", 1310, $1, $2, $3); }
| string_seq DDIV mul_div{ $$ = new Tree("mul div", 1310, $1, $2, $3); }
;
*/

/*
sp_seq: minus_string_seq
| minus_string_seq PLUS sp_seq{ $$ = new Tree("superposition seq", 1130, $1, $2, $3); }
| minus_string_seq MINUS sp_seq{ $$ = new Tree("superposition seq", 1130, $1, $2, $3); }
| comparison_expr
| comparison_expr PLUS sp_seq{ $$ = new Tree("superposition seq", 1130, $1, $2, $3); }
| comparison_expr MINUS sp_seq{ $$ = new Tree("superposition seq", 1130, $1, $2, $3); }
;
*/
sp_seq: minus_string_seq
| comparison_expr
| sp_seq PLUS sp_seq{ $$ = new Internal("superposition seq", 1130, $1, $2, $3); }
| sp_seq MINUS sp_seq{ $$ = new Internal("superposition seq", 1130, $1, $2, $3); }
;

/*
minus_string_seq: string_seq
| MINUS string_seq{ $$ = new Tree("minus string seq", 1150, $1, $2); }
;
*/

minus_string_seq: arith_expr
| MINUS arith_expr{ $$ = new Internal("minus string seq", 1150, $1, $2); }
;


seq_seq: sp_seq
| sp_seq DOT seq_seq{ $$ = new Internal("sequence seq", 1140, $1, $3); }
;

// assignment: ID EQUAL seq SEMICOLON{ $$ = new Tree("assignment", 1160, $1, $3); }
// assignment: id_bra_ket EQUAL seq SEMICOLON{ $$ = new Internal("assignment", 1160, $1, $3); }
// assignment: id_bra_ket EQUAL seq SEMICOLON{ $$ = new Assignment($1, $3); }
assignment: assignment_lhs EQUAL seq SEMICOLON{ $$ = new Assignment($1, $3); }
;

// global_assignment: GLOBAL id_bra_ket EQUAL seq SEMICOLON{ $$ = new Internal("global assignment", 1220, $2, $4); }
// global_assignment: GLOBAL assignment_lhs EQUAL seq SEMICOLON{ $$ = new Internal("global assignment", 1220, $2, $4); }
global_assignment: GLOBAL assignment_lhs EQUAL seq SEMICOLON{ $$ = new GlobalAssignment($2, $4); }
;

// op_assignment: id_bra_ket EQUAL_OP seq SEMICOLON{ $$ = new Internal("op assignment", 1340, $1, $2, $3); }
op_assignment: assignment_lhs EQUAL_OP seq SEMICOLON{ $$ = new Internal("op assignment", 1340, $1, $2, $3); }
;

// global_op_assignment: GLOBAL id_bra_ket EQUAL_OP seq SEMICOLON{ $$ = new Internal("global op assignment", 1350, $2, $3, $4); }
global_op_assignment: GLOBAL assignment_lhs EQUAL_OP seq SEMICOLON{ $$ = new Internal("global op assignment", 1350, $2, $3, $4); }
;

/*
id_bra_ket: ID
| LITERAL_KET
| LITERAL_BRA
;
*/

assignment_lhs: ID
| LITERAL_KET
| LITERAL_BRA
| star_id
| id_star
| assignment_lhs COMMA assignment_lhs{ $$ = new Internal("assignment lhs", 1480, $1, $3); }
;

star_id: STAR ID{ $$ = new Internal("star id", 1470, $2); }
;

id_star: ID STAR{ $$ = new Internal("id star", 1475, $1); }
;


// learn_rule: rule_lhs RULE seq SEMICOLON{ $$ = new Tree("learn rule", 1170, $1, $2, $3); } // Add rule_rhs when you are ready.
learn_rule: rule_lhs RULE rule_rhs SEMICOLON{ $$ = new Internal("learn rule", 1170, $1, $2, $3); }
;

rule_rhs: seq
// | SEMICOLON block_statements end_or_return{ $$ = new Tree("rule rhs", 1280, $2, $3); }
| SEMICOLON block_statements END_COLON{ $$ = new Internal("rule rhs", 1280, $2); }
;

chunk: AS seq COLON SEMICOLON chunk_rules END_COLON SEMICOLON{ $$ = new Internal("chunk", 1510, $2, $5); }
// chunk: AS seq COLON SEMICOLON chunk_rules END_COLON SEMICOLON{ $$ = new Chunk($2, $5); }
;

chunk_rules: chunk_rule
| chunk_rule chunk_rules{ $$ = new Internal("chunk rules", 1520, $1, $2); }
;

chunk_rule: ID RULE rule_rhs SEMICOLON{ $$ = new Internal("chunk rule", 1530, $1, $2, $3); } // rule_rhs vs seq on the rhs of a chunk_rule?
;


/*
end_or_return: END_COLON
| return_seq
;
*/

return_seq: RETURN seq{ $$ = new Internal("return seq", 1290, $2); } // move SEMICOLON to here? Probably!
;

error_seq: ERROR seq SEMICOLON{ $$ = new Internal("error seq", 1450, $2); }

/*
rule_lhs: ID ID{ $$ = new Tree("rule lhs", 1180, $1, $2); }
// | ID ket_or_seq{ $$ = new Tree("rule lhs", 1180, $1, $2); } // 6 S/R conflicts
| ID LITERAL_KET{ $$ = new Tree("rule lhs", 1180, $1, $2); } // 1 S/R conflict // fixed!
| ID bracket_seq{ $$ = new Tree("rule lhs", 1180, $1, $2); } // 1 S/R conflict // fixed!
| ID wildcard{ $$ = new Tree("rule lhs", 1180, $1, $2); }
;
*/

// rule_lhs: chain_seq  // redundant!
rule_lhs : chain
| ID wildcard{ $$ = new Internal("rule lhs", 1180, $1, $2); }
;

wildcard: DOT
| STAR
| DSTAR
;

// for_statement: FOR ID IN seq COLON SEMICOLON block_statements END_COLON SEMICOLON{ $$ = new Internal("for statement", 1230, $2, $4, $7); }
for_statement: FOR for_unpack IN seq COLON SEMICOLON block_statements END_COLON SEMICOLON{ $$ = new Internal("for statement", 1230, $2, $4, $7); }
;

for_unpack: ID
| ID COMMA ID{ $$ = new Internal("for unpack", 1500, $1, $3); }
| ID COMMA ID COMMA ID{ $$ = new Internal("for unpack", 1500, $1, $3, $5); }
;

block_statements: block_statement
| block_statement block_statements{ $$ = new Internal("block statements", 1240, $1, $2); }
;

block_statement: SEMICOLON
// | chain_seq SEMICOLON
| chain SEMICOLON
| assignment
| op_assignment
| global_assignment
| global_op_assignment
| learn_rule
| for_statement
| cfor_statement
| sfor_statement
| lfor_statement
// | end_or_return SEMICOLON // 2 S/R conflicts
| return_seq SEMICOLON
| if_statement
| while_statement
| BREAK /* loop specific statement? */
| CONTINUE /* loop specific statement? */
| init
| error_seq
;


cfor_statement: CFOR ID IN seq COLON SEMICOLON block_statements END_COLON SEMICOLON{ $$ = new Internal("cfor statement", 1250, $2, $4, $7); }
;

lfor_statement: LFOR ID IN seq COLON SEMICOLON block_statements END_COLON SEMICOLON{ $$ = new Internal("lfor statement", 1420, $2, $4, $7); }
;


sfor_statement: SFOR ID IN seq COLON SEMICOLON block_statements END_COLON SEMICOLON{ $$ = new Internal("sfor statement", 1260, $2, $4, $7); }
;

/*
if_statement: IF expr COLON SEMICOLON block_statements END_COLON{ $$ = new Tree("if statement", 1330, $2, $5); }
| IF expr COLON SEMICOLON block_statements ELSE block_statements END_COLON{ $$ = new Tree("if statement", 1330, $2, $5, $7); }
;
*/

if_statement: IF seq COLON SEMICOLON block_statements END_COLON{ $$ = new Internal("if statement", 1330, $2, $5); }
| IF seq COLON SEMICOLON block_statements ELSE block_statements END_COLON{ $$ = new Internal("if statement", 1330, $2, $5, $7); }
;

/*
expr: comparison_expr
| equality_expr
// | bool_expr
| chain_seq //%prec NO_LOGICAL_OP
;
*/

equality_expr: seq EQUALITY seq{ $$ = new Internal("equality expr", 1370, $1, $2, $3); }
| seq LOGICAL_OP seq{ $$ = new Internal("bool expr", 1380, $1, $2, $3); }
// | seq %prec NO_LOGICAL_OP // many S/R and R/R conflicts!
;

// bool_expr: LEFT_PAREN equality_expr RIGHT_PAREN LOGICAL_OP LEFT_PAREN equality_expr RIGHT_PAREN{ $$ = new Tree("bool expr", 1380, $2, $4, $6); }// 1 S/R
// bool_expr: equality_expr LOGICAL_OP equality_expr{ $$ = new Tree("bool expr", 1380, $1, $2, $3); }
/*
bool_expr: equality_expr
| equality_expr LOGICAL_OP bool_expr{ $$ = new Tree("bool expr", 1380, $1, $2, $3); }
;
*/


// while_statement: WHILE expr COLON SEMICOLON block_statements END_COLON{ $$ = new Tree("while statement", 1360, $2, $5); }
while_statement: WHILE seq COLON SEMICOLON block_statements END_COLON{ $$ = new Internal("while statement", 1360, $2, $5); }
;

init: INIT init_list SEMICOLON{ $$ = new Internal("init", 1390, $2); }
;

init_list: ID
| ID COMMA init_list{ $$ = new Internal("init list", 1400, $1, $3); }
;

/*
bra_ket: LITERAL_BRA LITERAL_KET{ $$ = new Internal("bra ket", 1410, $1, $2); }
| LITERAL_BRA chain LITERAL_KET{ $$ = new Internal("bra ket", 1410, $1, $2, $3); }
;
*/

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
    driver.parse_error_message += "\nError on token: " + driver.lexer->last_token.text;
    driver.parse_error_message += ", line " + std::to_string(driver.lexer->last_token.line);
    driver.parse_error_message += " column " + std::to_string(driver.lexer->last_token.col) + "\n";
    std::cout << driver.parse_error_message;
    driver.parse_error = true;
}
