#pragma once
#include "../Maze.h"

class WallFollower {
    private:
        inline static int startRow;
        inline static int startCol;
        inline static int exitRow;
        inline static int exitCol;

        inline static int previousRow;
        inline static int previousCol;

        inline static int currentRow;
        inline static int currentCol;
        inline static Maze::Direction currentDirection;

        inline static int startVisitsCounter;

    public:
        static void Init(int startingRow, int startingCol, int endRow, int endCol, Maze& maze);
        static void Solve(Maze &maze);
};