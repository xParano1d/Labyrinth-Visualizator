#pragma once
#include "../Grid.h"

class DepthFirstSearch {
    private:
        inline static vector<Grid::CellPosition> cellStack;
        inline static vector<vector<Grid::CellPosition>> parentMap;

        inline static Grid::CellPosition exit;

        inline static bool PathFound;
        inline static Grid::CellPosition cursor;
    public:
        static void Init(int startingRow, int startingCol, int exitRow, int exitCol, Grid& maze);
        static void Solve(Grid &maze);
};