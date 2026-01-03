#pragma once
#include "../Grid.h"
class Backtracking {
    private:
        inline static vector<Grid::CellPosition> cellStack;
    public:
        static void Init(int startingRow, int startingCol, Grid& maze);
        static void Generate(Grid& maze);
};