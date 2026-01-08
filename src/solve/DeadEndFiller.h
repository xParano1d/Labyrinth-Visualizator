#pragma once
#include "../Grid.h"

class DeadEndFiller {
    private:
    inline static Grid::CellPosition startCell;
    inline static Grid::CellPosition exitCell;
    
    inline static vector<Grid::CellPosition> deadEnd;
    inline static Grid::CellPosition currentCell;
    
    static int getwallCount(int row, int col, Grid &maze);

    inline static bool Filled;
    public:
        static void Init(int startingRow, int startingCol, int endingRow, int endingCol, Grid& maze);
        static void Solve(Grid &maze);
};