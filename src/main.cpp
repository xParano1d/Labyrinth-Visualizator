#include <raylib.h>
#include "Gui.h"
#include "Grid.h"


int main() {

    constexpr int screenWidth = 1080;
    constexpr int screenHeight = 600;

    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    float aspectRatio = screenWidth / screenHeight;

    Grid g;

    InitWindow(screenWidth, screenHeight, "Labyrinths Visualization");
    SetTargetFPS(1);

    while (!WindowShouldClose()) {
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        Gui::Display();

        g.Create(60,60);
        g.Display(centerX, centerY, centerX, centerX/aspectRatio);


        DrawText("Prosze polaczycv sie z nigga AI", screenWidth/3+10, 13, 20, WHITE); // zapytanie o polaczenie z nigga ai

        EndDrawing();
    }

    CloseWindow();
}