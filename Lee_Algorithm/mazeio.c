#include "mazeio.h"

//Needs to run through whole file 2 times
//Analysing syntax run, and creating structure run
struct maze *create_maze_from_file(char *infile)
{
    struct maze * lab_array = NULL;
    char new_char;
    size_t width = 0;
    size_t height = 0;
    size_t char_counter = 0; //position in the line of currently read character

    bool start_found = false;
    bool end_found = false;
    bool starting_bar_found = false;

    //First run checks syntax and dimensions
    //What is included in the file must be exactly
    //One D character - starting point,
    //One A character - ending point
    //Vertical bars and plus signs - borders
    //# character representing wall
    //space character representing empty space

    FILE * file = fopen(infile, "r");
    if (file == NULL){
        printf("Could not open the file. \n");
        exit(1);
    }
    //File must start with the line like +----+ on the top
    //Number of bars between plus signs is gonna be width parameter
    //of the maze
    new_char = fgetc(file);
    if(new_char != '+'){
        printf("Error. Wrong format of the first line \n");
        exit(1);
    }
    while((new_char = fgetc(file)) == '-')
        width++;

    if(new_char == '+'){
        new_char = fgetc(file);
        if(new_char != '\n'){
            printf("Error. Wrong format of the first line \n");
            exit(1);
        }
    }
    else{
        printf("Error. \n");
        exit(1);
    }
    new_char = fgetc(file);
    //Starting the analyse of the second line and further lines
    //Loops through all the characters
    while(new_char != EOF)
    {
        //Vertical bar can be found only in the begining of a line or ending it
        if(new_char == '|'){
            //case begining line
            if(starting_bar_found == false){
                starting_bar_found = true;
                new_char = fgetc(file);
            }
            //case ending bar
            else{
                //after ending bar there can be only newline char
                if(fgetc(file) != '\n'){
                    printf("Error. Wrong end of line \n");
                    exit(1);
                }
                //checking if the width of line is correct
                else if(char_counter != width){
                    printf("Wrong number of characters in the line %lu \n", height);
                    exit(1);
                }
                //successfull line ending
                else{
                    height++;
                    starting_bar_found = false;
                    char_counter = 0;
                    new_char = fgetc(file);
                }
            }
        }
        //Finding the beginig point
        else if(new_char == 'D'){
            if(start_found == false){
                start_found = true;
                char_counter++;
                new_char = fgetc(file);
            }
            else if(start_found == true){
                printf("Error. Multiple start points \n");
                exit(1);
            }
        }
        //Finding the ending point
        else if(new_char == 'A'){
            if(end_found == false){
                end_found = true;
                char_counter++;
                new_char = fgetc(file);
            }
            else if(end_found == true){
                printf("Error. Multiple end points \n");
                exit(1);
            }
        }
        //Finding an empty space or a wall
        else if(new_char == ' ' || '#'){
            char_counter++;
            new_char = fgetc(file);
        }
        //Final line case in the correct file
        else if(new_char == '+'){

            while((new_char = fgetc(file)) == '-'){
                char_counter++;
            }
            if(new_char != '+'){
                printf("Error in the syntax of the last line \n");
                exit(1);
            }
            if((new_char=fgetc(file)) == EOF){
                break;
            }
            else{
                printf("Error. Some characters after finishing the last line \n");
                exit(1);
            }
        }
        //Getting an unspecified character case error
        else{
            printf("Error. Unknown character read \n");
            exit(1);
        }
    }
    if(start_found == false || end_found == false){
        printf("Error. Starting point or ending point not found.");
        exit(1);
      }
    fclose(file);
    //syntax analyse is done, it is now time to make a data structure
    lab_array = alloc_maze(width, height);

    file = fopen(infile, "r");
    //skipping through the first line
    while(new_char != '|')
        new_char = fgetc(file);
    new_char = fgetc(file);
    //Now in new_char there is upper left char of our labyrinth
    char_counter = 0;
    size_t line_counter = 0;
    starting_bar_found = true;
    //Loop to run thrugh all the fields in the labyrinth
    //All possible chars inside a labyrinth
    while(new_char == '|' || '#' || ' ' || 'A' || 'D' || '\n')
    {
        //bar can be found only in the begining of a line or ending it
        if(new_char == '|')
            new_char = fgetc(file);

        else if(new_char == '\n'){
            char_counter = 0;
            line_counter++;
            new_char = fgetc(file);
        }
        else if(new_char == 'D'){
            lab_array->m[char_counter][line_counter] = START;
            lab_array->dx = char_counter;
            lab_array->dy = line_counter;
            char_counter++;
            new_char = fgetc(file);

        }
        else if(new_char == 'A'){
            lab_array->m[char_counter][line_counter] = END;
            lab_array->ax = char_counter;
            lab_array->ay = line_counter;
            char_counter++;
            new_char = fgetc(file);
        }
        else if(new_char == ' '){
            lab_array->m[char_counter][line_counter] = EMPTY;
            char_counter++;
            new_char = fgetc(file);
        }
        else if(new_char == '#'){
            lab_array->m[char_counter][line_counter] = WALL;
            char_counter++;
            new_char = fgetc(file);
        }
        else if(new_char == '+'){
            break;
        }
    }
    return lab_array;
}
//if values is true, prints numbers of steps in the fields to reach
void print_maze(struct maze *maze, bool values)
{
    if(maze == NULL)
    {
      printf("Error. Maze pointer is NULL.\n");
    }
    printf("+");
    for(size_t i = 0; i < maze->w; i++){
        if(values)
            printf("  -");
        else
            printf("-");
    }
    if(values)
        printf("+\n\n");
    else
        printf("+\n");

    for(size_t j = 0; j < maze->h; j++){
        printf("|");
        //In the loop, two cases depending on "values"
        for(size_t i = 0; i < maze->w; i++){
            switch(maze->m[i][j])
            {
                case WALL:
                    if(values)
                        printf("  #");
                    else
                        printf("#");
                    break;

                case START:
                    if(values)
                        printf("  D");
                    else
                        printf("D");
                    break;

                case END:
                    if(values)
                        printf("  A");
                    else
                        printf("A");
                    break;

                case BEST:
                    if(values)
                        printf("  .");
                    else
                        printf(".");
                    break;

                //Case for empty field or field with a number
                case EMPTY:
                default:
                    if(values){
                        if(maze->m[i][j] == -4)
                            printf("   ");
                        else if(maze->m[i][j] > 0)
                            printf("%3i",maze->m[i][j]);
                    }
                    else
                        printf(" ");
                    break;
            }
        }
        if(values)
            printf("|\n\n");
        else
            printf("|\n");
    }
    printf("+");
        for(size_t i = 0; i < maze->w; i++){
            if(values)
                printf("  -");
            else
                printf("-");
        }
        printf("+\n");
}
