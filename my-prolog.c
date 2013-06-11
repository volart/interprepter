#include <stdio.h>
#include <stdlib.h>
#include "my-prolog.h"

/*--------------------Argument--------------------------------*/

Argument* construct_argument(Argument_type type, void *data)
{
	Argument *arg = (Argument *)malloc(sizeof(Argument));
	arg->type = type;
	arg->data = data;
	return arg;
}

void destruct_argument(Argument* a)
{
	free(a);
}

/*-----------------------Arguments_list-----------------------*/

Arguments_list_elem* construct_arguments_list_elem(Argument *arg)
{
	Arguments_list_elem* e = (Arguments_list_elem*)malloc(sizeof(Arguments_list_elem));
	e->argument = (Argument*)malloc(sizeof(Argument));
	e->argument = arg;
	e->next_elem = NULL;
	return e;
}

void destruct_arguments_list_elem(Arguments_list_elem *e)
{
	free(e);
}

Arguments_list* construct_args_list()
{
	Arguments_list* alist = (Arguments_list*)malloc(sizeof(Arguments_list));
	alist->head = NULL;
	alist->tail = NULL;
	alist->size = 0;
	return alist;
}

void destruct_args_list(Arguments_list *alist)
{
	for (int i = 0; i < alist->size; i++) {
		Arguments_list_elem *temp = alist->head->next_elem;
		destruct_arguments_list_elem(alist->head);
		alist->head = temp;
	}
}

/*Добавление элемента к списку.*/
void add_args_list(Arguments_list *alist, Argument *arg)
{
	Arguments_list_elem *new_elem = construct_arguments_list_elem(arg);
	if (alist->tail != NULL) {
		alist->tail->next_elem = new_elem;
		alist->tail = new_elem;
	} else { /*список пуст*/
		alist->head = new_elem;
		alist->tail = new_elem;
	}
	alist->size++;
}


/*----------------------Predicate-----------------------------*/

Predicate* construct_predicate(char *name, Arguments_list *args)
{
	Predicate *p = (Predicate*)malloc(sizeof(Predicate));
	p->name = name;
	p->arguments = args;
	return p;
}

void destruct_predicate(Predicate *p)
{
	free(p);
}


/*-----------------------Clause-------------------------------*/

Clause* construct_clause(Predicate *head, Predicate *body)
{
	Clause *c = (Clause*)malloc(sizeof(Clause));
	c->head = head;
	c->body = body;
	return c;
}
void destruct_clause(Clause *c)
{
	free(c);
}

/*-----------------------Clause_list--------------------------*/

Clause_list_elem* construct_clause_list_elem(Clause *c)
{
	Clause_list_elem *e = (Clause_list_elem*)malloc(sizeof(Clause_list_elem));
	e->clause = c;
	return e;
}

void destruct_clause_list_elem(Clause_list_elem *e) {
	free(e);
}

Clause_list* construct_clause_list()
{
	Clause_list *clist = (Clause_list*)malloc(sizeof(Clause_list));
	clist->head = NULL;
	clist->tail = NULL;
	return clist;
}

void destruct_clause_list(Clause_list *clist)
{
	while (clist->head != NULL) {
		Clause_list_elem *temp = clist->head->next_elem;
		free(clist->head);
		clist->head = temp;
	}
}

/*Добавление выражения в список.*/
void add_clause_list(Clause_list *clist, Clause *clause)
{
	Clause_list_elem *new_elem = construct_clause_list_elem(clause);
	if (clist->tail != NULL) {
		clist->tail->next_elem = new_elem;
		clist->tail = new_elem;
	} else { /*список пуст*/
		clist->head = new_elem;
		clist->tail = new_elem;
	}
}


/*-----------------------debug--------------------------------*/

void print_argument(Argument *arg)
{
	switch (arg->type) {
		case ATOM_T:
			printf("%s:ATOM", (char*)arg->data);
			break;
		case INTEGER_T:
			printf("%d:INTEGER", *(int*)arg->data);
			break;
		case VARIABLE_T:
			printf("%s:VARIABLE", (char*)arg->data);
			break;
		}
}

void print_arguments_list(Arguments_list *args_list)
{
	Arguments_list_elem *ptr = args_list->head;
	while (ptr != args_list->tail) {
		print_argument(ptr->argument);
		printf(", ");
		ptr = ptr->next_elem;
	}
	print_argument(ptr->argument);
}

void print_predicate(Predicate *predicate)
{
	printf("%s", predicate->name);
	printf("(");
	print_arguments_list(predicate->arguments);
	printf(")");
	printf("; arity: %d", predicate->arguments->size);
}

void print_clause(Clause *clause)
{
	if (clause->body != NULL) {
		printf("rule : ");
		print_predicate(clause->head);
		printf(":-");
		print_predicate(clause->body);
	} else {
		printf("fact : ");
		print_predicate(clause->head);
	}
}

void print_clause_list(Clause_list *clist)
{
	Clause_list_elem *ptr = clist->head;
	while (ptr != NULL) {
		print_clause(ptr->clause);
		printf("\n");
		ptr = ptr->next_elem;
	}
}
