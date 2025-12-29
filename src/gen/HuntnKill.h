#pragma once
#include "../Grid.h"

class HuntnKill {
    private:
        inline static int highlightIterationRow;
        inline static int highlightIterationCol;
        inline static Grid::Cell *pLastCell;
        inline static Color lastCellColor;
        inline static bool unvisitedCellFound;

        inline static int currentRow;
        inline static int currentCol;

        static void Hunt(Grid& maze);
    public:
        static void Init(int startingRow, int startingCol, Grid &maze);
        static void Generate(Grid& maze);
};