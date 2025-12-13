#pragma once
#include "../Grid.h"

class Kruskal {
    private:
        struct Edge{
            Grid::CellPosition posA;
            Grid::Position direction;   //from A to B 
        };
    public:
        inline static vector<Edge> edgeList;

        static void Init(Grid& maze);
        static void Generate(Grid& maze);
};