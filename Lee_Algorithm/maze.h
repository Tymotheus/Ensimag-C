#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

//Structure representing considered maze
//Contains its fields, dimensions, cords of starting and ending points
struct maze {
    uint32_t w; // width of the maze
    uint32_t h; // height of the maze
    uint32_t dx; // x and y coords of the starting point
    uint32_t dy;
    uint32_t ax; // x and y coords of ending point
    uint32_t ay;
    int32_t **m; //array to store values of maze
    //top left is m[x][y]
};

/* value at each position is the number of steps to
   reach this position, or one of: */
#define WALL -1
#define START -2
#define END -3
#define EMPTY -4
#define BEST -5

/* Dynamically allocates memory for maze of size w*h.
   Set w, h and m, other fields and m values are not meaningful.
   Return NULL and print message to stderr if error.
*/
struct maze *alloc_maze(uint32_t w, uint32_t h);

/* frees all memory in maze */
void free_maze(struct maze *maze);

#endif
