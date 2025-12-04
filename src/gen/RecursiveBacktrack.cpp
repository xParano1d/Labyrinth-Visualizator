#include "../Grid.h"
#include <cstdlib>
#include <ctime>

static void Generate(int currentRow, int currentCol, Grid maze){
    //Add the current location to the visited set
    maze.grid[currentRow][currentCol].visited = true;

    bool chosenNeighbour = false;
    int neighbourRow;
    int neighbourCol;

    bool neighbourLeft = false;
    bool neighbourUp = false;
    bool neighbourRight = false;
    bool neighbourDown = false;

    if(currentCol-1 < maze.grid[currentRow].size() && !maze.grid[currentRow][currentCol-1].visited){    //Left
        neighbourLeft = true;
    }
    if(currentRow+1 < maze.grid.size() && !maze.grid[currentRow+1][currentCol].visited){                //Up
        neighbourUp = true;
    }
    if(currentCol+1 < maze.grid[currentRow].size() && !maze.grid[currentRow][currentCol+1].visited){    //Down
        neighbourRight = true;
    }
    if(currentRow-1 < maze.grid.size() && !maze.grid[currentRow-1][currentCol].visited){                //Right
        neighbourDown = true;
    }

    // While the current cell has any unvisited neighbour cells
    while(!chosenNeighbour){
        srand(time(0));
        int r = rand() % 5;
        //Skip if the neighbor has already been visited
        switch (r){
        case 0:     //left
            if(neighbourLeft){
                chosenNeighbour = true;
                neighbourRow = currentRow;
                neighbourCol = currentCol - 1;
            }
            break;
        case 1:     //Up
            if(neighbourUp){
                chosenNeighbour = true;
                neighbourRow = currentRow + 1;
                neighbourCol = currentCol;
            }
            break;
        case 2:     //Right
            if(neighbourRight){
                chosenNeighbour = true;
                neighbourRow = currentRow;
                neighbourCol = currentCol + 1;
            }
            break;
        case 3:     //Down
            if(neighbourDown){
                chosenNeighbour = true;
                neighbourRow = currentRow - 1;
                neighbourCol = currentCol;
            }
            break;
        default:
            chosenNeighbour = false;
            break;
        }
    }

    //Todo Add a passage from the current location to the neighbor

}