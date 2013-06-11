#ifndef _MY_PROLOG_H_
#define _MY_PROLOG_H_

typedef enum Argument_type_e
	{ATOM_T, INTEGER_T, VARIABLE_T}
	Argument_type;


/*--------------------------Argument--------------------------*/

/*Аргумент предиката. Может быть атомом, числом или переменной.*/
typedef struct Argument_s
{
	Argument_type type;
	void *data;
} Argument;

Argument* construct_argument(Argument_type type, void *data);
void destruct_argument(Argument* a);


/*-----------------------Arguments_list-----------------------*/

/*Элемент списка аргументов.*/
typedef struct Arguments_list_elem_s
{
    Argument *argument;
	struct Arguments_list_elem_s *next_elem;
} Arguments_list_elem;

Arguments_list_elem* construct_arguments_list_elem(Argument *arg);
void destruct_arguments_list_elem(Arguments_list_elem *e);

/*Список аргументов предиката.*/
typedef struct Arguments_list_s
{
	Arguments_list_elem *head;
	Arguments_list_elem *tail;
	int size;
} Arguments_list;

Arguments_list* construct_args_list();
void destruct_args_list(Arguments_list *alist);
/*Добавление элемента к списку.*/
void add_args_list(Arguments_list *alist, Argument *arg);


/*----------------------Predicate-----------------------------*/

/*Выражение вида name(arg1, arg2, ..., argn).*/
typedef struct Predicate_s
{
	char* name;
	Arguments_list *arguments;
} Predicate;

Predicate* construct_predicate(char *name, Arguments_list *args);
void destruct_predicate(Predicate *p);

/*-----------------------Clause-------------------------------*/

/*Факт или правило.*/
typedef struct Clause_s
{
    Predicate *head;
	Predicate *body; /*body == NULL, если выражение является фактом*/
} Clause;

Clause* construct_clause(Predicate *head, Predicate *body);
void destruct_clause(Clause *c);

/*-----------------------Clause_list--------------------------*/

typedef struct Clause_list_elem_s
{
	Clause *clause;
	struct Clause_list_elem_s *next_elem;
} Clause_list_elem;

Clause_list_elem* construct_clause_list_elem(Clause *c);
void destruct_clause_list_elem(Clause_list_elem *e);

typedef struct Clause_list_s
{
	Clause_list_elem *head;
	Clause_list_elem *tail;
} Clause_list;

Clause_list* construct_clause_list();
void destruct_clause_list(Clause_list *clist);

/*Добавление выражения в список.*/
void add_clause_list(Clause_list *clist, Clause *clause);


/*-----------------------debug--------------------------------*/

void print_argument(Argument *arg);
void print_arguments_list(Arguments_list *args_list);
void print_predicate(Predicate *predicate);
void print_clause(Clause *clause);
void print_clause_list(Clause_list *clist);

#endif /* _MY_PROLOG_H_ */
