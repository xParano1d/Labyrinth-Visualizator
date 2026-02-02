#include "Sidewinder.h"

void Sidewinder::Init(Maze& maze) {
    maze.CreateEmpty(maze.rows, maze.columns);
    currentRow = 0;
    currentCol = 0;
    runStartCol = 0;
    maze.Generated = false;
}

void Sidewinder::Generate(Maze& maze) {
    if (maze.Generated) return;

    // boundaries
    bool atEasternBoundary = (currentCol == maze.columns - 1);
    bool atNorthernBoundary = (currentRow == 0);
    
    bool shouldCloseRun = atEasternBoundary;
    
    if (!atEasternBoundary && !atNorthernBoundary) {
        shouldCloseRun = (GetRandomValue(0, 1) == 0); // 50% chance
    }

    if (shouldCloseRun) {
        
        int winnerCol = GetRandomValue(runStartCol, currentCol);
        
        // We can only carve North if we are not in the first row
        if (!atNorthernBoundary) {
            maze.grid[currentRow][winnerCol].topWall = false;
            maze.grid[currentRow - 1][winnerCol].bottomWall = false;
            
            // Visual: Flash the north connection
            maze.grid[currentRow - 1][winnerCol].color = {108, 117, 148, 255};
        }
        
        // Mark current as visited
        maze.grid[currentRow][currentCol].color = {108, 117, 148, 255};

        // The run is over. The next run starts at the next column.
        runStartCol = currentCol + 1;

    } else {
        // CONTINUE RUN: Carve East
        maze.grid[currentRow][currentCol].rightWall = false;
        maze.grid[currentRow][currentCol + 1].leftWall = false;
        
        // Mark current as visited
        maze.grid[currentRow][currentCol].color = {108, 117, 148, 255};
    }
    
    currentCol++;

    if (currentCol >= maze.columns) {
        currentRow++;
        currentCol = 0;
        runStartCol = 0; // Reset run for new row
    }

    if (currentRow >= maze.rows) {
        maze.Generated = true;
    }
}