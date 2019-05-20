/***************************************************
*********Maze_Genegation:_Eller's_Algorithm*********
***************************************************/

#include "consts.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
* memory allocation for a sx*sy array
*/
int **  map_mem_alloc(int sx, int sy) {
	int ** map;
	int i;
	map = (int**)malloc(sizeof(int*) * sy); 
	map[0] = (int*)malloc(sizeof(int) * sx * sy);
	for(i = 1; i < sy; ++i)
		 map[i] = map[i - 1] + sx;
	return map;
}

/*							#######
* first filling of the map 	#     #
* with a template			# # # #
*							#     #
*	 map example   7x5		# # # #
*                            
*/								
int ** map_first_fill(int ** map, int sx, int sy) {
	int x;
	int y;
	
	for(y = 0; y < sy; ++y) {
		for(x = 0; x < sx; ++x) {
			if(x == 0 || y == 0 || x == sx - 1)
				map[y][x] = WALL;
			else if(x % 2 == 0 && y % 2 == 0)
				map[y][x] = WALL;
			else 
				map[y][x] = EMPTY;
		}
	}
	return map;
}

void rand_3_walls(int m_x, int m_y, struct Maze * maze, int point) { 
	int walls;
	int x, y;
	while(1) {
		if(walls == 3 && maze->map[y*2+1][x*2+1] == EMPTY)
			break;
		x = rand() % m_x;
		walls = 0;
		for(int i = 0; walls != 3 && i < 10; ++i) {
			y = rand() % m_y;
			walls = 0;
			if (maze->map[y * 2][x * 2 + 1] == WALL)
				walls++;
			if (maze->map[y * 2 + 1][x * 2] == WALL)
				walls++;
			if (maze->map[y * 2 + 2][x * 2  + 1] == WALL)
				walls++;
			if (maze->map[y * 2 + 1][x * 2 + 2] == WALL)
				walls++;
		}
	}
	maze->map[y * 2 + 1][x * 2 + 1] = point;
}

/*******************************************************
*                  generation function                 *
*******************************************************/
struct Maze * gen_eller(int sx, int sy) {
	if(sx % 2 == 0)
		sx--;
	if(sy % 2 == 0)
		sy--;

	struct Maze * maze;
	maze = (struct Maze *)malloc(sizeof(struct Maze));
	maze->sx = sx;	
	maze->sy = sy;
	int x;
	int y;

	maze->map = map_mem_alloc(sx, sy);	
	maze->map = map_first_fill(maze->map, sx, sy);
	

/*
*								#######		
* array of maze cells 			#0 1 2#
* to fill with number of sets	# # # #
*								#3 4 5#
*								#######
*/
	int m_set_y = (sy - 1) / 2;
	int m_set_x = (sx - 1) / 2;
//	int map_sets[m_set_y + 1][m_set_x + 1]; 				//static
	int ** map_sets;										//dinamic
	map_sets = map_mem_alloc(m_set_x + 1, m_set_y + 1);	
	int set_number = 1; //number of a connectivity set
 
	for(x = 0; x < m_set_x + 1; ++x)						//first line generation
		map_sets[0][x] = 0;

	for(y = 0; y < m_set_y; ++y) {							//loop along lines 
		
	/*
	*	put a new set numbers where there is no set (number == 0)
	*/
		for(x = 0; x < m_set_x; ++x) {						
			if(map_sets[y][x] == 0) {
				map_sets[y][x] = set_number;
				++set_number;
			}
		}
	
	/*
	* side walls installation	
	*/
		for(x = 0; x < m_set_x; ++x) {
			if(map_sets[y][x] == map_sets[y][x+1])			// put a wall between cells 
				maze->map[y*2 + 1][x*2 + 2] = WALL;			// with the same sets

			else if(rand() % 2 == 1)
				maze->map[y*2 + 1][x*2 + 2] = WALL;			//at random put a wall
	
			else if(x < m_set_x - 1) {						//if we don't put a wall
				int right_set = map_sets[y][x + 1]; 
				int left_set = map_sets[y][x];
				for(int i = 0; i < m_set_x; ++i) {
					if(map_sets[y][i] == right_set)
						map_sets[y][i] = left_set;			 //combine the sets
				}
			}
		}

	/*
	*	bottom walls installation
	*/
		int bottom_wall = 1; //1 if no cells without bottom wall in the  current set
	
		for(x = 0; x < m_set_x; ++x) {
			if(map_sets[y][x] != map_sets[y][x+1]) {
				if(bottom_wall); 							//don't put a wall
				else									
					if(rand() % 5 == 1)					
						maze->map[y*2 + 2][x*2 + 1] = WALL;
				bottom_wall = 1;
			}
			else if(rand() % 2 == 1)
				maze->map[y*2 + 2][x*2 + 1] = WALL;
			else
				bottom_wall = 0;
		}

	/*
	*	preparation for the next line
	*/
		for(x = 0; x < m_set_x + 1; ++x)
			map_sets[y+1][x] = map_sets[y][x];				//copy current line 

		for(x = 0; x < m_set_x; ++x) {
			if(maze->map[y*2 + 2][x*2 + 1] == WALL)
				map_sets[y + 1][x] = 0;
		}

	}
	
/*
*	last line generation		
*/
	--y;
	for(x = 0; x < m_set_x - 1; ++x) {
		if(map_sets[y][x] != map_sets[y][x+1]) {			// no wall between cells 
			maze->map[y*2 + 1][x*2 + 2] = EMPTY;			// of different sets
		
			int right_set = map_sets[y][x + 1]; 
			int left_set = map_sets[y][x];
			for(int i = 0; i < m_set_x; ++i) {
				if(map_sets[y][i] == right_set)
					map_sets[y][i] = left_set;				 //combine the sets
			}
		}
	}
	
/*
*	bottom wall line of the maze
*/
	
	for(x = 0; x < m_set_x; ++x)
		maze->map[y*2 + 2][x*2 + 1] = WALL;
/*
*	start and finish generation
*/
	if(sx * sy > 9) {
		rand_3_walls(m_set_x, m_set_y, maze, IN);				//start
		rand_3_walls(m_set_x, m_set_y, maze, OUT);				//finish
	}

	return maze;
}
