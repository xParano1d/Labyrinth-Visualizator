#include "WallFollower.h"

void WallFollower::Init(int startingRow, int startingCol, int endRow, int endCol, Maze &maze) {
    startRow = startingRow;
    startCol = startingCol;
    exitRow = endRow;
    exitCol = endCol;

    currentRow = startingRow;
    currentCol = startingCol;


    previousRow = startingRow;
    previousCol = startingCol;
    
    maze.grid[startingRow][startingCol].color = {108, 117, 148, 255};
    currentDirection = Maze::Direction::DOWN;

    startVisitsCounter = 0;
}

void WallFollower::Solve(Maze &maze) {
    if (maze.Solved || maze.Impossible) return;

    bool right = false;
    bool front = false;

    if(currentRow == exitRow && currentCol == exitCol){
        maze.Solved = true;
        maze.grid[currentRow][currentCol].color = WHITE;
    }else if(!maze.Solved){
        
        switch (currentDirection){
            case (Maze::Direction::LEFT):
                if(maze.grid[currentRow][currentCol].topWall || currentRow == 0){  //? is there wall on right?
                    right = true;
                }
                if(maze.grid[currentRow][currentCol].leftWall || currentCol == 0){ //? is there wall in front?
                    front = true;
                }
            break;
            
            case (Maze::Direction::UP):
                if(maze.grid[currentRow][currentCol].rightWall || currentCol == maze.columns - 1){
                    right = true;
                }
                if(maze.grid[currentRow][currentCol].topWall || currentRow == 0){
                    front = true;
                }
            break;
            
            case (Maze::Direction::RIGHT):
                if(maze.grid[currentRow][currentCol].bottomWall || currentRow == maze.rows - 1){
                    right = true;
                }
                if(maze.grid[currentRow][currentCol].rightWall || currentCol == maze.columns - 1){
                    front = true;
                }
            break;
            
            case (Maze::Direction::DOWN):
                if(maze.grid[currentRow][currentCol].leftWall || currentCol == 0){
                    right = true;
                }
                if(maze.grid[currentRow][currentCol].bottomWall || currentRow == maze.rows - 1){
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
                    case (Maze::Direction::LEFT):
                    currentDirection = Maze::Direction::DOWN;
                    break;
                
                    case (Maze::Direction::UP):
                        currentDirection = Maze::Direction::LEFT;
                    break;
                
                    case (Maze::Direction::RIGHT):
                        currentDirection = Maze::Direction::UP;
                    break;
                
                    case (Maze::Direction::DOWN):
                        currentDirection = Maze::Direction::RIGHT;
                    break;
                
                    default:
                    break;
                }

            }else{
                //Do not turn. Move forward one step.
                switch (currentDirection){
                    case (Maze::Direction::LEFT):
                        currentCol--;
                    break;
                
                    case (Maze::Direction::UP):
                        currentRow--;
                    break;
                    
                    case (Maze::Direction::RIGHT):
                        currentCol++;
                    break;
                    
                    case (Maze::Direction::DOWN):
                        currentRow++;
                    break;
                    
                    default:
                    break;
                }

            }
        }else{
            //Turn 90° to the Right and move forward one step.
            switch (currentDirection){
                case (Maze::Direction::LEFT):
                    currentDirection = Maze::Direction::UP;
                    currentRow--;
                break;
                    
                case (Maze::Direction::UP):
                    currentDirection = Maze::Direction::RIGHT;
                    currentCol++;
                break;
                    
                case (Maze::Direction::RIGHT):
                    currentDirection = Maze::Direction::DOWN;
                    currentRow++;
                break;
            
                case (Maze::Direction::DOWN):
                    currentDirection = Maze::Direction::LEFT;
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

            // Check for Impossible state
            if (currentRow == startRow && currentCol == startCol) {
                startVisitsCounter++;
                //since it starts there couter should be always 1 (in theory)
                if(startVisitsCounter>4){
                    maze.Impossible = true;
                }
            }
        }

    }
}
