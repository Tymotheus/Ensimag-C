#include <stdio.h>
#include <string.h>
#include "mazeio.h"
#include "lee.h"

int main(int argc, char *argv[])
{
    // if(argc != 2 || argv[1]=="-h" || argv[1]=="--help"){
    //     printf("Valid use: program_name [name of file storing maze to analyse] \n");
    //     exit(1);
    // }
    if(argc != 2 || strcmp(argv[1],"-h")==0 || strcmp(argv[1],"--help")==0){
        printf("Valid use: program_name [name of file storing maze to analyse] \n");
        exit(1);
    }
    struct maze * labirynt = create_maze_from_file(argv[1]);

    print_maze(labirynt, false);
    bool solution_found = solve_maze(labirynt);
    if(solution_found)

        build_path(labirynt);
    print_maze(labirynt, true);

    free_maze(labirynt);
    return 0;
}
