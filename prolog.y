%{
#include <stdio.h>
#include "prolog.h"

void yyerror(const char* str) 
{
	 fprintf(stderr, "error: %s\n", str);
}

void main()
{
	 yyparse();
}


%}

%token DELIMITER POINT QUESTION VARIABLE ATOM INTEGER LPAREN RPAREN COMMA

%%
program: 		clause_list
				{
					printf("clause_list\n");
				}
		| 		query
				{
					printf("query\n");
				}
				;

clause_list: 	clause
		| 		clause_list clause
				;
				
clause: 		fact
		| 		rule
				;

fact: 			predicate POINT
				;
rule: 			predicate DELIMITER predicate POINT
				;

query: 			QUESTION predicate POINT
				;

predicate: 		ATOM LPAREN arguments RPAREN
				;

arguments: 		argument
		| 		arguments COMMA argument
				;

argument: 		ATOM
		| 		VARIABLE
		| 		INTEGER
				;

%%
