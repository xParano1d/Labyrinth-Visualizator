#include "WallFollower.h"

void WallFollower::Init(int startingRow, int startingCol, Grid &maze) {
    
    currentRow = startingRow;
    currentCol = startingCol;
    
    previousRow = startingRow;
    previousCol = startingCol;
    
    maze.grid[startingRow][startingCol].color = {108, 117, 148, 255};
    currentDirection = Grid::Position::DOWN;

}

void WallFollower::Solve(Grid &maze) {
    bool right = false;
    bool front = false;

    if(currentRow == maze.rows-1 && currentCol == maze.columns-1){
        maze.Solved = true;
        maze.grid[currentRow][currentCol].color = WHITE;
    }else if(!maze.Solved){
        
        switch (currentDirection){
            case (Grid::Position::LEFT):
                if(maze.grid[currentRow][currentCol].topWall){  //? is there wall on right?
                    right = true;
                }
                if(maze.grid[currentRow][currentCol].leftWall){ //? is there wall in front?
                    front = true;
                }
            break;
            
            case (Grid::Position::UP):
                if(maze.grid[currentRow][currentCol].rightWall){
                    right = true;
                }
                if(maze.grid[currentRow][currentCol].topWall){
                    front = true;
                }
            break;
            
            case (Grid::Position::RIGHT):
                if(maze.grid[currentRow][currentCol].bottomWall){
                    right = true;
                }
                if(maze.grid[currentRow][currentCol].rightWall){
                    front = true;
                }
            break;
            
            case (Grid::Position::DOWN):
                if(maze.grid[currentRow][currentCol].leftWall){
                    right = true;
                }
                if(maze.grid[currentRow][currentCol].bottomWall){
                    front = true;
                }
                break;

            default:
            break;
        }



        if(right){
            if(front){
                // Turn 90° to the Left. Do not move yet.
                switch (currentDirection){
                    case (Grid::Position::LEFT):
                    currentDirection = Grid::Position::DOWN;
                    break;
                
                    case (Grid::Position::UP):
                        currentDirection = Grid::Position::LEFT;
                    break;
                
                    case (Grid::Position::RIGHT):
                        currentDirection = Grid::Position::UP;
                    break;
                
                    case (Grid::Position::DOWN):
                        currentDirection = Grid::Position::RIGHT;
                    break;
                
                    default:
                    break;
                }

            }else{
                //Do not turn. Move forward one step.
                switch (currentDirection){
                    case (Grid::Position::LEFT):
                        currentCol--;
                    break;
                
                    case (Grid::Position::UP):
                        currentRow--;
                    break;
                    
                    case (Grid::Position::RIGHT):
                        currentCol++;
                    break;
                    
                    case (Grid::Position::DOWN):
                        currentRow++;
                    break;
                    
                    default:
                    break;
                }

            }
        }else{
            //Turn 90° to the Right and move forward one step.
            switch (currentDirection){
                case (Grid::Position::LEFT):
                    currentDirection = Grid::Position::UP;
                    currentRow--;
                break;
                    
                case (Grid::Position::UP):
                    currentDirection = Grid::Position::RIGHT;
                    currentCol++;
                break;
                    
                case (Grid::Position::RIGHT):
                    currentDirection = Grid::Position::DOWN;
                    currentRow++;
                break;
            
                case (Grid::Position::DOWN):
                    currentDirection = Grid::Position::LEFT;
                    currentCol--;
                break;
                    
                default:
                break;
                }
                
            }

        
        if(previousRow != currentRow || previousCol != currentCol){
            
            if (!maze.solvePath.empty() && maze.solvePath.back().A.row == currentRow && maze.solvePath.back().A.col == currentCol){

                maze.deadEndPath.push_back(maze.solvePath.back());

                maze.solvePath.pop_back();

            }else{

                maze.solvePath.push_back({{previousRow, previousCol}, {currentRow, currentCol}});
            }

            maze.grid[previousRow][previousCol].color = WHITE;
            maze.grid[currentRow][currentCol].color = {108, 117, 148, 255};

            previousRow = currentRow;
            previousCol = currentCol;
        }
    }
}
