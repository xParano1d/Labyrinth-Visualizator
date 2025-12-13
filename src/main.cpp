#include <iostream>
#include <raylib.h>
#include "Gui.h"
#include "./gen/Backtracking.h"
#include "./gen/HuntnKill.h"
#include "./gen/Prim.h"
#include "./gen/Kruskal.h"


int main() {
    //settings
    constexpr int screenWidth = 1080;
    constexpr int screenHeight = 600;
    int gridWidth = 20;
    int gridHeight = 20;
    float vSpeed = 100;                   //visualization speed (delay in seconds between iterations)
    // 0.1 -> fast      5 -> slow
    vSpeed = 1 / vSpeed;


    Grid grid;
    Gui gui;


    InitWindow(screenWidth, screenHeight, "Labyrinths Visualization");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)time(NULL));
    
    double delay;
    double genTime;

    gui.Init();
    grid.Create(gridHeight, gridWidth);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        gui.Display();

        if(gui.readyGen){

            gui.genState = gui.GenHandle();

            switch(gui.genState){
                case (Gui::Algorithm::Backtracking):
                    grid.Create(gridHeight, gridWidth);
                    Backtracking::Init(0, 0, grid);
                    gui.readyGen = false;
                break;
                
                case (Gui::Algorithm::HuntNKill):
                    grid.Create(gridHeight, gridWidth);
                    HuntnKill::Init(0, 0, grid);
                    gui.readyGen = false;
                break;
                
                case (Gui::Algorithm::Prim):
                    grid.Create(gridHeight, gridWidth);
                    Prim::Init(0, 0, grid);
                    gui.readyGen = false;
                break;
                
                case (Gui::Algorithm::Kruskal): //Randomized* Kruskal
                    grid.Create(gridHeight, gridWidth);
                    Kruskal::Init(grid);
                    gui.iterations--;
                    gui.readyGen = false;
                break;
                
                case (Gui::Algorithm::None):
                break;
            }

            if(!gui.readyGen){
                gui.algTime = 0;
                gui.iterations = 0;
                gui.iterations++;
                delay = GetTime();
                genTime = GetTime();
            }

        }else{
            gui.algTime = GetTime() - genTime;
            
            switch (gui.genState){
                case (Gui::Algorithm::Backtracking):
                    if(GetTime()-delay > vSpeed){
                        if(!grid.stack.empty()){
                            Backtracking::Generate(grid);
                            gui.iterations++;
                            delay = GetTime();
                        }else{
                            if(GetTime()-delay > vSpeed*2){
                                grid.ChangeEveryCellColor(WHITE);
                                gui.genState = Gui::Algorithm::None;
                                gui.readyGen = true;
                            }
                        }
                    }
                break;
                
                case (Gui::Algorithm::HuntNKill):
                    if(GetTime()-delay > vSpeed){
                        if(grid.UnvisitedCount()>0){
                            HuntnKill::Generate(grid);
                            gui.iterations++;
                            delay = GetTime();
                        }else{
                            if(GetTime()-delay > vSpeed*2){
                                grid.ChangeEveryCellColor(WHITE);
                                gui.readyGen = true;
                                gui.genState = Gui::Algorithm::None;
                            }
                        }
                    }
                break;
               
                case (Gui::Algorithm::Prim):
                    if(GetTime()-delay > vSpeed){
                        if(!Prim::frontierList.empty()){
                            Prim::Generate(grid);
                            gui.iterations++;
                            delay = GetTime();
                        }else{
                            if(GetTime()-delay > vSpeed*2){
                                grid.ChangeEveryCellColor(WHITE);
                                gui.readyGen = true;
                                gui.genState = Gui::Algorithm::None;
                            }
                        }
                    }
                break;
                
                case (Gui::Algorithm::Kruskal):
                    if(GetTime()-delay > vSpeed){
                        if(grid.UnvisitedCount()>0){
                            Kruskal::Generate(grid);
                            gui.iterations++;
                            delay = GetTime();
                        }else{
                            if(GetTime()-delay > vSpeed*2){
                                grid.ChangeEveryCellColor(WHITE);
                                gui.genState = Gui::Algorithm::None;
                                gui.readyGen = true;
                            }
                        }
                    }
                break;
                
                case (Gui::Algorithm::None):
                break;
            }
        }


        
        grid.Display();
        
        DrawText("Prosze polaczycv sie z nigga AI", screenWidth/3+10, 13, 20, BLUE); //! zapytanie o polaczenie z nigga ai
        EndDrawing();
    }

    CloseWindow();
}