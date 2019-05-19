#include "list.h"
#include <stdio.h>

int main()
{
	int d = -1;
	struct list * l = list_create(0);

	int a = 0;
	printf("commands: \n 1 push front \n 2 push back \n 3 pop front \n 4 pop back \n 5 print \n 6 search(return number) \n 0 exit from test program \n");
						

	while(d != 0)
	{
		switch(d)
		{
			case 1:
				printf("push_front\n");
				printf("Enter data:\n");
				scanf("%d", &a);
				push_front(l, a);
				print_list(l);
			break;
			case 2:
				printf("push_back\n");
				printf("Enter data:\n");
				scanf("%d", &a);
				push_back(l, a);
				print_list(l);
			break;
			case 3:
				printf("pop_front\n");
				pop_front(l);
				print_list(l);
			break;
			case 4:
				printf("pop_back\n");
				pop_back(l);
				//printf("%d %d\n", l -> first -> data, l -> last -> data);
				print_list(l);
			break;
			case 5:
				print_list(l);
			break;
			case 6:
				printf("search\n");
				printf("Enter data:\n");
				scanf("%d", &a);
				printf("%p \n", search(l, a));
			break;

		}
		printf("Enter command: ");
		scanf("%d", &d);
	}
}

