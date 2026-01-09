#include "DepthFirstSearch.h"

void DepthFirstSearch::Init(int startingRow, int startingCol, int exitRow, int exitCol, Grid &maze) {
    //clearing
    maze.UnvisitEveryCell();

    cellStack.clear();
    parentMap.clear();
    parentMap.resize(maze.grid.size(), vector<Grid::CellPosition>(maze.grid[0].size()) );

    //preaparing
    cellStack.push_back({startingRow, startingCol});

    parentMap[startingRow][startingCol] = {startingRow, startingCol};

    exit = {exitRow, exitCol};
    PathFound = false;
}

void DepthFirstSearch::Solve(Grid &maze) {
    if(!cellStack.empty() && !PathFound){
        //Get the cell at the very top of the stack:
        Grid::CellPosition currentCell = cellStack.back();
        cellStack.pop_back();
        //check if visited
        if(!maze.grid[currentCell.row][currentCell.col].visited){
            //if not then visit and proceed
            maze.grid[currentCell.row][currentCell.col].visited = true;
            maze.grid[currentCell.row][currentCell.col].color = {108, 117, 148, 255};

            if(currentCell == exit){
                PathFound = true;   //path is ready to be traced
                cursor = {currentCell.row, currentCell.col};
            }else if(!PathFound){
                //Scan and Process Neighbors
                vector<Grid::Position> v = maze.UnvisitedNeighbours(currentCell);
                
                for(Grid::Position p : v){
                    int neighbourRow = currentCell.row;
                    int neighbourCol = currentCell.col;
                    bool validNeighbour = false;

                    switch (p){
                        case Grid::Position::LEFT:
                            neighbourCol--;
                            if(!maze.grid[currentCell.row][currentCell.col].leftWall && !maze.grid[neighbourRow][neighbourCol].rightWall){
                                validNeighbour = true;
                            }
                        break;
                            
                        case Grid::Position::UP:
                            neighbourRow--;
                            if(!maze.grid[currentCell.row][currentCell.col].topWall && !maze.grid[neighbourRow][neighbourCol].bottomWall){
                                validNeighbour = true;
                            }
                        break;

                        case Grid::Position::RIGHT:
                            neighbourCol++;
                            if(!maze.grid[currentCell.row][currentCell.col].rightWall && !maze.grid[neighbourRow][neighbourCol].leftWall){
                                validNeighbour = true;
                            }
                        break;
                        
                        case Grid::Position::DOWN:
                            neighbourRow++;
                            if(!maze.grid[currentCell.row][currentCell.col].bottomWall && !maze.grid[neighbourRow][neighbourCol].topWall){
                                validNeighbour = true;
                            }
                        break;
                    }
                    if(validNeighbour){
                        //Mark Visited
                        maze.grid[neighbourRow][neighbourCol].color = {46, 52, 230, 255};
                        //Set Parent
                        parentMap[neighbourRow][neighbourCol] = {currentCell.row, currentCell.col};
                        //push to stack
                        cellStack.push_back({neighbourRow, neighbourCol});
                    }

                }

            }
        }

    }else if(PathFound){
        Grid::CellPosition parentCell = parentMap[cursor.row][cursor.col];

        if(cursor == parentCell){   //if reached starting cell
            maze.Solved = true; //done
        }else{
            //trace path
            maze.solvePath.push_back({cursor, parentCell});
            //move closer to starting Cell
            cursor = parentCell;
        }
    }
}