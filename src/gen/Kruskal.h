#pragma once
#include "../Grid.h"

class Kruskal {
    private:
        
    public:
        inline static vector<Grid::Edge> edgeList;

        static void Init(Grid& maze);
        static void Generate(Grid& maze);
};