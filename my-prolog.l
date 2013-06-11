%{
#include <stdio.h>
#include <string.h>
#include "my-prolog.tab.h"

extern YYSTYPE yylval;
%}

%%
":-"				   	return DELIMITER;
"."						return POINT;
"?-"					return QUESTION;
[_A-Z][_a-zA-Z0-9]*		yylval = (void*)strdup(yytext); return VARIABLE;
[a-z][_a-zA-Z0-9]*		yylval = (void*)strdup(yytext); return ATOM;
[0-9]+					yylval = (void*)strdup(yytext); return INTEGER;
"("						return LPAREN;
")"						return RPAREN;
","						return COMMA;
[ \t\n]					;
%%
