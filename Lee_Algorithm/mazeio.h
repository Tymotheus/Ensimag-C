#ifndef _MAZEIO_H_
#define _MAZEIO_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "maze.h"

/* Read maze definition from file named infile.
   Allocate and initialize a struct maze with
   values in WALL, START, END, or EMPTY.
   Print error message to stderr and return NULL
   if an error occurred (eg if infile does not
   correspond to a valid maze).
*/
struct maze *create_maze_from_file(char *infile);

/* Print the maze to stdout.
   If values==false, format: one space per char,
   print the WALL, START, END and BEST positions,
   using appropriate characters (eg # for WALL and
   "." for BEST).
   If values==true, format:  3 space per char and
   print the number of steps to reach
   each position (useful for debugging)
*/
void print_maze(struct maze *maze, bool values);

#endif
