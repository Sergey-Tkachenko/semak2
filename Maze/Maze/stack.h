#ifndef __STACK_H__
#define __STACK_H__

#include "consts.h"

struct Stack_node {
	struct Step step;
	struct Stack_node* next;
};

struct Stack {
	struct Stack_node* top;
};

struct Stack* create_stack();
void delete_stack(struct Stack*);

struct Step pop(struct Stack*);
void push(struct Stack*, struct Step);
char empty(struct Stack*);

#endif //__STACK_H__
