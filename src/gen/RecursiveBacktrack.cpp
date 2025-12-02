#include "../Grid.h"
#include <cstdlib>
#include <ctime>

static void Generate(int currentRow, int currentCol, Grid maze){
    //Add the current location to the visited set
    maze.grid[currentRow][currentCol].visited = true;

    bool chosenNeighbour = false;
    int neighbourRow;
    int neighbourCol;

    //Loop over all four neighbors of the current location in random order
    while(!chosenNeighbour){
        srand(time(0));
        int r = rand() % 5;
        //Skip if the neighbor has already been visited
        switch (r){
        case 0:     //left
            if(currentCol-1 < maze.grid[currentRow].size()){
                if(!maze.grid[currentRow][currentCol-1].visited){
                    chosenNeighbour = true;
                    neighbourRow = currentRow;
                    neighbourCol = currentCol - 1;
                }
            }
            break;
        case 1:     //Up
            if(currentRow+1 < maze.grid.size()){
                if(!maze.grid[currentRow+1][currentCol].visited){
                    chosenNeighbour = true;
                    neighbourRow = currentRow + 1;
                    neighbourCol = currentCol;
                }
            }
            break;
        case 2:     //Right
            if(currentCol+1 < maze.grid[currentRow].size()){
                if(!maze.grid[currentRow][currentCol+1].visited){
                    chosenNeighbour = true;
                    neighbourRow = currentRow;
                    neighbourCol = currentCol + 1;
                }
            }
            break;
        case 3:     //Down
            if(currentRow-1 < maze.grid.size()){
                if(!maze.grid[currentRow-1][currentCol].visited){
                    chosenNeighbour = true;
                    neighbourRow = currentRow - 1;
                    neighbourCol = currentCol;
                }
            }
            break;
        }
    }

    //Todo Add a passage from the current location to the neighbor

}