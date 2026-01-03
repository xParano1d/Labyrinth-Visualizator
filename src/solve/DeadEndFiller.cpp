#include "DeadEndFiller.h"

void DeadEndFiller::Init(int startingRow, int startingCol, Grid &maze) {
    cellStack.clear();

}

void DeadEndFiller::Solve(Grid &maze) {
    if(!cellStack.empty()){
        if(!Filled){
            //filling every cell with wallCount>3
            //and its neighbours (until we get to hallway)
        }else{
            //path after filling
        }



    }else{
        maze.Solved = true;
    }
}
