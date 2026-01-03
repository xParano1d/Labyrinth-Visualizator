#pragma once
#include "../Grid.h"

class DeadEndFiller {
    private:
        inline static vector<Grid::CellPosition> cellStack;
        
        inline static bool Filled;
    public:
        static void Init(int startingRow, int startingCol, Grid& maze);
        static void Solve(Grid &maze);
};