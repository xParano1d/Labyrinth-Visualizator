#pragma once
#include <vector>
#include <raylib.h>
using std::vector;

class Grid {
    public:
        int rows;
        int columns;
        
        struct CellPosition {
            int row;
            int col;
        };
        vector<CellPosition> stack;

        enum Position {
            LEFT,
            UP,
            RIGHT,
            DOWN
        };

        struct Edge{
            Grid::CellPosition posA;
            Grid::CellPosition posB;
            Grid::Position direction;   //from A to B 
        };
        
        struct Cell{
            bool rightWall;
            bool leftWall;
            bool topWall;
            bool bottomWall;

            Color color;

            bool visited = false;

            int groupID = 0; 
        };
        vector<vector<Cell>> grid;

        void Create(int rows, int columns);
        void Display();

        void ChangeEveryCellColor(Color c);
        void HighlightRow(int row, Color c);

        void ChangeGroupsID(int fromID, int toID);

        vector<CellPosition> GetUnvisitedNeighboursPosition(int cellRow, int cellCol);
        vector<Position> UnvisitedNeighbours(int cellRow, int cellCol);
        vector<Position> VisitedNeighbours(int cellRow, int cellCol);
        int UnvisitedCount();

    private:
        bool highlightRow = false;
        int highlightedRow;
        Color highlightColor;
};