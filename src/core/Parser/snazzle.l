%{
	#include "../../../src/SemantiKet.h"
	#include <iostream>
	using namespace std;
	extern int yylex();

	#define YY_NO_UNISTD_H

%}

%option c++
%option debug
%option yywrap nounput

%%
[ \t\n]+ ;
[0-9]+\.[0-9]+ { cout << "Found a floating-point number:" << yytext << endl; }
[0-9]+ { cout << "Found an integer:" << yytext << endl; }
[a-zA-Z0-9]+ { cout << "Found a string: " << yytext << endl; }
. ;
%%

