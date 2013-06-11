%{
#include <stdio.h>
#include "prolog.tab.h"
%}

%%
":-"				   	return DELIMITER;
"."						return POINT;
"?-"					return QUESTION;
[_A-Z][_a-zA-Z0-9]*		return VARIABLE;
[a-z][_a-zA-Z0-9]*		return ATOM;
[0-9]+					return INTEGER;
"("						return LPAREN;
")"						return RPAREN;
","						return COMMA;
[ \t\n]					;
%%
