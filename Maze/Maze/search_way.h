#include "list.h"
#include "consts.h"
#include <stdio.h>
void Lee(struct Maze * maze)
{
	//Search start
	int sy = maze -> sy;
	int sx = maze -> sx;

	struct Point start;
	struct Point fin;
	for(int i = 0; i < sy; ++i)
		for(int j = 0; j < sx; ++j)
		{
			if(maze -> map[i][j] == IN)
			{
				start.x = j;
				start.y = i;
			}
			if(maze -> map[i][j] == OUT)
			{
				fin.x = j;
				fin.y = i;
			}
		}

	//search way
	struct list * l = list_create(start);
	int counter = 1; 
	int f = 0;
	while((!empty(l)) && (f == 0))
	{
		struct list * sub_l = list_create_null();
		//add neighbour pts
		while(!empty(l))
		{
			struct Point p = pop_front(l) -> data;
			int x = p.x;
			int y = p.y;
	
			//printf("%d %d\n", x, y);
			if(maze -> map[y][x] == OUT)
			{
				f = 1;
				maze -> map[y][x] = counter;
				//printf("%d\n", counter); 
				break;
			}

			maze -> map[y][x] = counter;
			if((maze -> map[y -1][x] == EMPTY) || (maze -> map[y - 1][x] == OUT))
			{
				p.x = x;
				p.y = y - 1;
				push_back(sub_l, p);
			}


			if((maze -> map[y + 1][x] == EMPTY) || (maze -> map[y + 1][x] == OUT))
			{
				p.x = x;
				p.y = y + 1;
				push_back(sub_l, p);
			}
		
		
			if((maze -> map[y][x - 1] == EMPTY) || (maze -> map[y][x - 1] == OUT))
			{
				p.x = x - 1;
				p.y = y;
				push_back(sub_l, p);
		
			}	

			if((maze -> map[y][x + 1] == EMPTY) || (maze -> map[y][x + 1] == OUT))
			{
				p.x = x + 1;
				p.y = y;
				push_back(sub_l, p);
			}
		}
		l = sub_l;
		counter ++;
		//printf("I did this step correctly\n"); 
	}
	//search yacheicka with lowest natural number around fin
	if(f == 1)
	{
		//printf("%d\n", maze -> map[fin.y][fin.x]);
		int x = fin.x;
		int y = fin.y;
		//maze -> map[start.y][start.x] = IN;
		int steps = 0;
		while(maze -> map[y][x] != 1)
		{
			printf("%d %d\n", x, y);	
			maze -> map[y][x] = HERO;
			if(maze -> map[y -1][x] == counter - 1)
			{
				x = x;
				y = y - 1;
				printf("gg\n");
			}


			if(maze -> map[y + 1][x] == counter - 1)
			{
				x = x;
				y = y + 1;
				printf("gg\n");
			}
		
		
			if(maze -> map[y][x - 1] == counter - 1)
			{
				x = x - 1;
				y = y;
				printf("gg\n");
		
			}

			if(maze -> map[y][x + 1] == counter - 1)
			{
				x = x + 1;
				y = y;
				printf("gg\n");
			}
			counter --;
			steps++;
		}
		steps -= 2;		
		printf("STEPS: =  %d", steps);
	}
	
	maze -> map[start.y][start.x] = IN;
	maze -> map[fin.y][fin.x] = OUT;




	
	
	

}
