#include "Random.h"

void Random::FindStartAndExit(Maze &maze) {
    if (!pStartRow || !pStartCol || !pExitRow || !pExitCol) return;

    // 1. Find Top Row Start
    for(int j = 0; j < maze.columns; j++){
        if(maze.grid[0][j].wallCount()<4){
            *pStartRow = 0;
            *pStartCol = j;
            break;
        }
    }

    // 2. Find Bottom Row Exit
    for(int j = maze.columns - 1; j >= 0; j--){ 
        if(maze.grid[maze.rows - 1][j].wallCount()<4){
            *pExitRow = maze.rows - 1;
            *pExitCol = j;
            break; 
        }
    }
}

void Random::Init(int &startRow, int &startCol, int &exitRow, int &exitCol, Maze &maze) {
    //Clearing whole maze walls
    maze.ClearWalls();
    
    pStartRow = &startRow;
    pStartCol = &startCol;
    pExitRow = &exitRow;
    pExitCol = &exitCol;

    currentRow = 0;
    currentCol = 0;

    // Random Density between 25% and 45%
    density = GetRandomValue(25, 45);
}

void Random::Generate(Maze &maze) {
    if(currentRow>=0 && currentRow<maze.rows){
        if(currentCol>=0 && currentCol<maze.columns){

            if(GetRandomValue(0, 100) < density){
                //filling Cells as BLACK BLOCKS
                maze.grid[currentRow][currentCol].color = BLACK;

                //close all walls around it
                maze.grid[currentRow][currentCol].rightWall = true;
                maze.grid[currentRow][currentCol].leftWall = true;
                maze.grid[currentRow][currentCol].topWall = true;
                maze.grid[currentRow][currentCol].bottomWall = true;

                vector<Maze::Direction> n = maze.Neighbours({currentRow, currentCol});
                for(Maze::Direction d : n){
                    switch (d){
                        case Maze::Direction::LEFT:
                            maze.grid[currentRow][currentCol-1].rightWall = true;
                        break;
                            
                        case Maze::Direction::UP:
                            maze.grid[currentRow-1][currentCol].bottomWall= true;
                        break;

                        case Maze::Direction::RIGHT:
                            maze.grid[currentRow][currentCol+1].leftWall = true;
                        break;
                        
                        case Maze::Direction::DOWN:
                            maze.grid[currentRow+1][currentCol].topWall = true;
                        break;
                    }
                }
            }else{
                maze.grid[currentRow][currentCol].color = WHITE;
            }

            currentCol++;
        }else{
            currentRow++;
            currentCol = 0;
        }
    }else{  //Generated fully
        if(!maze.Generated){
            FindStartAndExit(maze);
            maze.Generated = true;
        }
    }
}
