#pragma once
#include "../Maze.h"

class Random {
    private:
        inline static int* pStartRow = nullptr;
        inline static int* pStartCol = nullptr;
        inline static int* pExitRow = nullptr;
        inline static int* pExitCol = nullptr;

        inline static int currentRow;
        inline static int currentCol;

        inline static int density;

        static void FindStartAndExit(Maze &maze);
    public:
        static void Init(int &startRow, int &startCol, int &exitRow, int &exitCol, Maze &maze);
        static void Generate(Maze& maze);
};