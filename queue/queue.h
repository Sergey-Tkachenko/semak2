
typedef int _data_type; 

#include "list.h"

struct queue
{
	struct Node * top;
	struct Node * end;
};


struct queue * create_queue(_data_type x)
{
	struct list * l = list_create(x);
	struct queue * q;
	q -> top = l -> first;
	q -> end = l -> last;
	return q;
}


void push(struct queue * q, _data_type x)
{
		
}
