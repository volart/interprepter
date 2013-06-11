#ifndef _PROLOG_H_
#define _PROLOG_H_

enum Argument_type {ATOM_T, INTEGER_T, VARIABLE_T}

struct Argument
{
    Argument_type type; /*аргумент может быть атомом, числом или переменной*/
	void *data;
};

#endif /* _PROLOG_H_ */
