#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "consts.h"

struct Queue_node {
	struct Step step;
	struct Queue_node* next;
};

struct Queue {
	struct Queue_node* top;
};

struct Queue* create_stack();
void delete_stack(struct Queue*);

struct Step pop(struct Queue*);
void push(struct Queue*, struct Step);
char empty(struct Queue*);

#endif //__QUEUE_H__
