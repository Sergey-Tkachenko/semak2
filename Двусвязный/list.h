#ifndef _LIST_H_

#define _LIST_H_

#ifndef _data_type
	typedef int _data_type;
#endif

#include <stdlib.h>
#include <stdio.h>
struct Node
{
	struct Node * prev;
	struct Node * next;
	_data_type data;
};

struct list
{
	struct Node * first;
	struct Node * last;
};


int empty(struct list * l);

struct list * list_create(_data_type x)
{
	struct list * l = (struct list *)malloc(sizeof(struct list));
	struct Node * s = (struct Node *)malloc(sizeof(struct Node));
	s -> prev = NULL;
	s -> next = NULL;
	s -> data = x;
	l -> first = s;
	l -> last = s;
	printf("%p %p %p %p %p\n", l, l->first, l->last, s->next, s->prev);
	return l;
}

struct Node * first(struct list * l)
{
	return 	l -> first;
}

struct Node * last(struct list * l)
{
	return l -> last;	
}

void push_front(struct list * l, _data_type x)
{
	
	if(!empty(l))
	{
		struct Node * t = (struct Node *)malloc(sizeof(struct Node));
		t -> data = x;
		t -> prev = NULL;
		t -> next = l -> first;
		l -> first -> prev = t;
		l -> first = t;
	}
	else
	{
		*l = *list_create(x);	
	}
}

void push_back(struct list * l, _data_type x)
{
	if(!empty(l))
	{
		struct Node * t = (struct Node *)malloc(sizeof(struct Node));
		t -> data = x;
		t -> next = NULL;
		t -> prev = l -> last;
		l -> last -> next = t;
		l -> last = t;
	}
	else
	{
		*l = *list_create(x);	
	}
}

int empty(struct list * l)
{
	return (l -> first == NULL)||(l -> last == NULL);	
}


struct Node * pop_back(struct list * l)
{
	struct Node * t = l -> last;
	if( (empty(l)) || (l -> first == l -> last))
	{
		l -> first = l -> last = NULL;
		printf("Stack is empty!!!\n");	
	}
	else
	{
		l -> last = l -> last -> prev;
		l -> last -> next = NULL;
	}
	return t;

}


struct Node * pop_front(struct list * l)
{
	struct Node * t = l -> first;
	if( (empty(l)) || (l -> first == l -> last))
	{
		printf("here\n");
		l -> first = l -> last = NULL;
		printf("Stack is empty!!!\n");	
	}
	else
	{
		l -> first = l -> first -> next;
		l -> first -> prev = NULL;
	}
	return t;
}


struct Node * search(struct list * l, _data_type x)
{

	struct Node * t = l -> first;
	while(t != NULL)
	{
		if(t -> data == x)
		{
			break;	
		}
		else
		{
			t = t -> next;	
		}

	}
	return t;
}



void print_list(struct list * l)
{
	struct Node * t = l -> first;
	while(t != NULL)
	{
		printf("%d ", t -> data);
		t = (t -> next);
	}
	printf("\n");
}
#endif
