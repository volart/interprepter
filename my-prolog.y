%{
#define YYSTYPE void*

#include <stdio.h>
#include "my-prolog.h"

void yyerror(const char* str) 
{
	 fprintf(stderr, "error: %s\n", str);
}

Clause_list *clause_list;

void main()
{
	clause_list = construct_clause_list();

	yyparse();

	print_clause_list(clause_list);
	destruct_clause_list(clause_list);
}


%}

%token DELIMITER POINT QUESTION VARIABLE ATOM INTEGER LPAREN RPAREN COMMA

%%
program: 		clause_list
				{
					$$ = $1;
				}
		| 		query
				{
					printf("query\n");
				}
				;

clause_list: 	clause
				{
					add_clause_list(clause_list, (Clause *)$1);
					$$ = clause_list;
				}
		| 		clause_list clause
				{
					add_clause_list(clause_list, (Clause *)$2);
					$$ = clause_list;
				}
				;
				
clause: 		fact
				{
					$$ = $1;
				}
		| 		rule
				{
					$$ = $1;
				}
				;

fact: 			predicate POINT
				{
					Clause *clause = construct_clause((Predicate*)$1, NULL);
					$$ = (void*)clause;
				}
				;
rule: 			predicate DELIMITER predicate POINT
				{
					Clause *clause = construct_clause((Predicate*)$1, (Predicate*)$3);
					$$ = (void*)clause;
				}
				;

query: 			QUESTION predicate POINT
				;

predicate: 		ATOM LPAREN arguments RPAREN
				{
					Predicate *p = construct_predicate((char*)$1, (Arguments_list*)$3);
					$$ = (void*)p;
				}
				;

arguments: 		argument
				{
					/*создаём список из одного элемента*/
					Arguments_list *args_list = construct_args_list();
					add_args_list(args_list, (Argument*)$1);
					$$ = (void*)args_list;

				}
		| 		arguments COMMA argument
				{
					/*добавляем аргумент в уже имеющийся список*/
					add_args_list((Arguments_list*)$1, (Argument*)$3);
					$$ = (void*)$1;
				}
				;

argument: 		ATOM
				{
					Argument *arg = construct_argument(ATOM_T, $1);
					$$ = (void*)arg;
				}
		| 		VARIABLE
				{
					Argument *arg = construct_argument(VARIABLE_T, $1);
					$$ = (void*)arg;
				}
		| 		INTEGER
				{
					/*преобразуем строку в число*/
					int *n = (int*)malloc(sizeof(int));
					*n = atoi((char*)$1);

					Argument *arg = construct_argument(INTEGER_T, n);
					$$ = (void*)arg;
				}
				;

%%
