%{
	#include <iostream>
    using namespace std;

    #include "../../../src/SemantiKet.h"
#include "../../../src/winflexbison/FlexLexer.h"

    // Declare stuff from Flex that Bison needs to know about:
    extern int yylex();
    extern int yyparse();

    void yyerror(const char* s);
%}

%union {
	int ival;
	float fval;
	char* sval;
}

%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%%
snazzle:
INT snazzle{
    cout << "bison found an int: " << $1 << endl;
}
| FLOAT snazzle  {
    cout << "bison found a float: " << $1 << endl;
}
| STRING snazzle {
    cout << "bison found a string: " << $1 << endl; free($1);
}
| INT            {
    cout << "bison found an int: " << $1 << endl;
}
| FLOAT          {
    cout << "bison found a float: " << $1 << endl;
}
| STRING         {
    cout << "bison found a string: " << $1 << endl; free($1);
}
;
%%

void yyerror(const char* s) {
    cout << "EEK, parse error!  Message: " << s << endl;
    // might as well halt now:
    exit(-1);
}