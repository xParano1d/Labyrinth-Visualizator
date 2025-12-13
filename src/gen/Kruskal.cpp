#include "Kruskal.h"

void Kruskal::Init(Grid &maze) {
    //Throw all of the Edges into set
    for (int i = 0; i < (int)maze.grid.size(); i++){        
        for (int j = 0; j < (int)maze.grid[i].size(); j++){

            if(j >= 0 && j < (int)maze.grid[i].size()-1){     //Right Edge
                edgeList.push_back({{i, j}, Grid::Position::RIGHT});
            }

            if(i >= 0 && i < (int)maze.grid.size()-1){        //Bottom Edge
                edgeList.push_back({{i, j}, Grid::Position::DOWN});
            }

        }
    }
}

void Kruskal::Generate(Grid &maze) {
    //Select and Remove an edge from the bag at random.
    int random = GetRandomValue(0, (int)edgeList.size()-1);
    Edge currentEdge = edgeList[random];

    edgeList.erase(edgeList.begin()+random);

    int currentRow = currentEdge.posA.row;
    int currentCol = currentEdge.posA.col;

    //Remove walls between Cells
    switch (currentEdge.direction){
        case Grid::Position::LEFT:
        break;

        case Grid::Position::UP:
        break;

        case Grid::Position::RIGHT:
            maze.grid[currentRow][currentCol].rightWall = false;
            maze.grid[currentRow][currentCol+1].leftWall = false;

            //Mark the Group as visited
            maze.grid[currentRow][currentCol+1].visited = true;
            maze.grid[currentRow][currentCol+1].color = {108, 117, 148, 255};
        break;

        case Grid::Position::DOWN:
            maze.grid[currentRow][currentCol].bottomWall = false;
            maze.grid[currentRow+1][currentCol].topWall = false;

            //Mark the Group as visited
            maze.grid[currentRow+1][currentCol].visited = true;
            maze.grid[currentRow+1][currentCol].color = {108, 117, 148, 255};
        break;
    }

    //Mark the Group as visited
    maze.grid[currentRow][currentCol].visited = true;
    maze.grid[currentRow][currentCol].color = {108, 117, 148, 255};

}