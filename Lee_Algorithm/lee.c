#include "lee.h"

//struct used while solving the maze
//it holds cords and the distance beetween it and the starting point
struct algo_list{
    uint32_t x_position;
    uint32_t y_position;
    int32_t step_distance;
};

bool valid_cords(int32_t x, int32_t y, struct maze *maze)
{
    return(x>= 0 && x < (int32_t) maze->w && y>=0 && y < (int32_t) maze->h ); //&& maze->m[x][y]!='#'
}

//Gets a maze and writes in some empty spaces of it
//number of steps necessary to reach this field
bool solve_maze(struct maze *maze)
{
    //list structure is storing the fields which neighbours
    //we will be analysing
    struct algo_list list[maze->w * maze->h];
    struct algo_list temp = {maze->dx, maze->dy, 0};
    list[0] = temp;
    uint32_t to_add = 1; //index on which will be added new cell of the list
    uint32_t to_analyse = 0; //index of next cell which is going to be checked
    bool solution_found = false;

    //loop for checking neighbours and updating step values
    //iterates till solution found or all fields added to the list checked
    while(solution_found == false && to_analyse < to_add)
    {
        //we take a new element of the list, not analysed yet
        //and we take its neighbours
        int32_t x = list[to_analyse].x_position;
        int32_t y = list[to_analyse].y_position;
        //whith each step we increase the distance we need to reach a field
        int32_t steps = list[to_analyse].step_distance + 1;
        //2 loops to check all 4 neighbours
        int32_t x_neighbours[4] = {x-1, x+1, x, x};
        int32_t y_neighbours[4] = {y, y, y-1, y+1};
        for(int i = 0; i < 4; i++)
        {
                //checking the validity of a field
                if(valid_cords(x_neighbours[i],y_neighbours[i],maze)){
                    //found the end
                    if(maze->m[x_neighbours[i]][y_neighbours[i]] == END){
                        //printf("Case1\n");
                        printf("Ending point found!\n");
                        solution_found = true;
                        break;
                    }
                    //field not seen yet, not tagged
                    else if(maze->m[x_neighbours[i]][y_neighbours[i]] == EMPTY){
                        //printf("Case2\n");
                        maze->m[x_neighbours[i]][y_neighbours[i]] = steps;
                        struct algo_list temp = {x_neighbours[i], y_neighbours[i], steps};
                        //printf("Writing value %i in field x=%i y=%i\n",steps, x_neighbours[i],y_neighbours[i]);
                        list[to_add] = temp;
                        //printf("Adding this field to position %i in the list\n",to_add);
                        to_add++;
                    }
                    //field already seen, already tagged or wall
                    else{
                        continue;
                    }
                }
                //field beyond the borders
                else
                    continue;
        }
        //incrementing, to start the analyse of a next element of the List
        //in the next iteration
        to_analyse++;
    }
    if(solution_found==false)
        printf("There is no solution found by me :( \n");
    return solution_found;
}

/*First, maze must be solved by solve_maze funtion
By that time it holds numbers of steps needed to reach particular empty field.
Then algorithm builds the way backwards, starting from the ending field,
and choosing adjacent fields with the shortest distance.
Then it puts '.' char int the fields of the maze, representing the path*/
void build_path(struct maze *maze)
{
    //cords of currently analysed cell - we start with an end cell
    uint32_t x = maze->ax;
    uint32_t y = maze->ay;
    //initialising variable, needed to choose shortest path
    uint32_t min_range = maze->w * maze->h;
    while( x != maze->dx || y != maze->dy)
    {
        int32_t x_neighbours[4] = {x-1, x+1, x, x};
        int32_t y_neighbours[4] = {y, y, y-1, y+1};
        for(int i = 0; i<4; i++)
        {

            if( valid_cords(x_neighbours[i], y_neighbours[i], maze) )
            {
                //printf("%i Neighbour cords: x=%i y=%i values: %i \n", i, x_neighbours[i], y_neighbours[i], maze->m[x_neighbours[i]][y_neighbours[i]]);

                if(maze->m[x_neighbours[i]][y_neighbours[i]] == START){
                    x = x_neighbours[i];
                    y = y_neighbours[i];
                    printf("Path built! \n");
                    break;
                }
                //found new optimal field leading to
                else if( maze->m[x_neighbours[i]][y_neighbours[i]] > 0 && (uint32_t) maze->m[x_neighbours[i]][y_neighbours[i]] < min_range)
                {
                    min_range = maze->m[x_neighbours[i]][y_neighbours[i]];
                    x = x_neighbours[i];
                    y = y_neighbours[i];
                    //printf("Writing: min_range is now %i \n", min_range);
                }
                //wall, not optimal path, or already marked
                else{
                    continue;
                }
            }
            //cords beyond the borders
            else{
                continue;
            }
        }
        //tagging a path between end and begining
        if(x != maze->dx || y != maze->dy)
        {
            maze->m[x][y]= BEST;
            // printf("x=%i y=%i tagged \n",x,y );
            // printf("Min range = %i \n", min_range);
        }
    }
}
