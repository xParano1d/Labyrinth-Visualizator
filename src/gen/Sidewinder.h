#pragma once
#include "../Maze.h"

class Sidewinder {
private:
    inline static int currentRow;
    inline static int currentCol;
    inline static int runStartCol;

public:
    static void Init(Maze& maze);
    static void Generate(Maze& maze);
};