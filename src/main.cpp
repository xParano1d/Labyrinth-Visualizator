#include <iostream>
#include <raylib.h>
#include "Gui.h"
#include "./gen/Backtracking.h"
#include "./gen/HuntnKill.h"
#include "./gen/Prim.h"
#include "./gen/Kruskal.h"


int main() {
    constexpr int screenWidth = 1080;
    constexpr int screenHeight = 600;

    //settings
    int gridWidth = 20;
    int gridHeight = 20;

    int startingRow = 0;
    int startingCol = 0;

    float vSpeed = 20;     //visualization speed 
    vSpeed = 1 / vSpeed;    //heighest value -> faster
    



    Grid grid;
    Gui gui;


    InitWindow(screenWidth, screenHeight, "Labyrinths Visualization");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)time(NULL));
    
    double delay;
    double genTime;
    // double solveTime;
    bool algType;       // true -> Gen  |  false -> solve

    gui.Init();
    grid.Create(gridHeight, gridWidth);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        gui.Display();

        if(gui.ready){

            gui.choosenAlgorithm = gui.MainButtonHandler();

            switch(gui.choosenAlgorithm){
                case (Gui::Algorithm::Backtracking):
                    grid.Create(gridHeight, gridWidth);
                    Backtracking::Init(startingRow, startingCol, grid);
                    algType = true;
                break;
                
                case (Gui::Algorithm::HuntNKill):
                    grid.Create(gridHeight, gridWidth);
                    HuntnKill::Init(startingRow, startingCol, grid);
                    algType = true;
                break;
                
                case (Gui::Algorithm::Prim):
                    grid.Create(gridHeight, gridWidth);
                    Prim::Init(startingRow, startingCol, grid);
                    algType = true;
                break;
                
                case (Gui::Algorithm::Kruskal): //Randomized* Kruskal
                    grid.Create(gridHeight, gridWidth);
                    Kruskal::Init(grid);
                    gui.genIterations--;
                    algType = true;
                break;


                case (Gui::Algorithm::None):
                break;


                case (Gui::Algorithm::HandOnWall):

                break;

                case (Gui::Algorithm::ShortestPath):

                break;

                case (Gui::Algorithm::DeadEndFiller):
                    std::cout << "test" << std::endl;
                break;
            }

            if(!gui.ready){
                if(algType){        //GENERATION
                    gui.genIterations = 0;
                    gui.genIterations++;

                    gui.genTime = 0;
                    genTime = GetTime();
                }else{              //SOLVING
                    gui.solveIterations = 0;
                    gui.solveIterations++;

                    gui.solveTime = 0;
                    // solveTime = GetTime();
                }
                delay = GetTime();
            }

        }else{
            gui.genTime = GetTime() - genTime;
            
            switch (gui.choosenAlgorithm){
                case (Gui::Algorithm::Backtracking):
                    if(GetTime()-delay > vSpeed){
                        if(!grid.stack.empty()){
                            Backtracking::Generate(grid);
                            gui.genIterations++;
                            delay = GetTime();
                        }else{
                            grid.generated = true;
                        }
                    }
                break;
                
                case (Gui::Algorithm::HuntNKill):
                    if(GetTime()-delay > vSpeed){
                        if(grid.UnvisitedCount()>0){
                            HuntnKill::Generate(grid);
                            gui.genIterations++;
                            delay = GetTime();
                        }else{
                            grid.generated = true;
                        }
                    }
                break;
               
                case (Gui::Algorithm::Prim):
                    if(GetTime()-delay > vSpeed){
                        if(!Prim::frontierList.empty()){
                            Prim::Generate(grid);
                            gui.genIterations++;
                            delay = GetTime();
                        }else{
                            grid.generated = true;
                        }
                    }
                break;
                
                case (Gui::Algorithm::Kruskal):
                    if(GetTime()-delay > vSpeed){
                        if(!Kruskal::edgeList.empty()){
                            Kruskal::Generate(grid);
                            gui.genIterations++;
                            delay = GetTime();
                        }else{
                            grid.generated = true;
                        }
                    }
                break;
                

                case (Gui::Algorithm::None):
                break;


                case (Gui::Algorithm::HandOnWall):
                    gui.ready = true;
                    gui.choosenAlgorithm = Gui::Algorithm::None;
                break;

                case (Gui::Algorithm::ShortestPath):
                    gui.ready = true;
                    gui.choosenAlgorithm = Gui::Algorithm::None;
                break;

                case (Gui::Algorithm::DeadEndFiller):
                    gui.ready = true;
                    gui.choosenAlgorithm = Gui::Algorithm::None;
                break;
            }


            gui.solveReady = grid.generated;

            if(grid.generated){
                if(GetTime()-delay > vSpeed*2){
                    grid.ChangeEveryCellColor(WHITE);
                    gui.ready = true;
                    gui.choosenAlgorithm = Gui::Algorithm::None;
                }
            }
        }

        
        grid.Display();
        
        DrawText("Prosze polaczycv sie z nigga AI", screenWidth/3+10, 13, 20, GREEN); //! zapytanie o polaczenie z nigga ai
        EndDrawing();
    }

    CloseWindow();
}