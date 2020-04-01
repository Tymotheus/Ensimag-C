#include <stdlib.h>
#include "maze.h"


struct maze *alloc_maze(uint32_t w, uint32_t h)
{
    struct maze *temp = calloc(1, sizeof(struct maze));
    if(temp == NULL){
      printf("Could not allocate memory \n");
      return NULL;
    }
    temp->w = w;
    temp->h = h;
    temp->m = calloc(w, sizeof(int32_t *));
    for(uint32_t i = 0; i<w; i++){
        temp->m[i] = calloc(h, sizeof(int32_t ));
    }
    temp->dx = 0;
    temp->dy = 0;
    temp->ax = 0;
    temp->ay = 0;
    return temp;
}

void free_maze(struct maze *maze)
{
  if(maze == NULL)
  {
    printf("Maze is a NULL pointer, nothing to free.\n");
    exit(0);
  }
  for(uint32_t i = 0; i < maze->w; i++){
      free(maze->m[i]);
    }
  free(maze->m);
  free(maze);
  printf("Maze pointer freed\n");
}
