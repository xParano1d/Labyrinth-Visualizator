#include "Gui.h"
#include <raylib.h>
#include <filesystem>
#include <string>
#include <iostream>
using namespace std;
namespace fs = std::filesystem;

Rectangle Gui::LeftContext = { 0.0f, 0.0f, 0.0f, 0.0f };
Rectangle Gui::CenterContext = { 0.0f, 0.0f, 0.0f, 0.0f };
Rectangle Gui::RightContext = { 0.0f, 0.0f, 0.0f, 0.0f };

void Gui::Display(){
    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    
    //Boxes settings
    float offsetX = screenWidth * 0.01;         // x4 on width
    float offsetY = screenHeight * 0.02;        // x2   on height
    float smallBoxWidth = screenWidth * 0.2;   // x2 on width
    float bigBoxWidth = screenWidth * 0.56;     // x1 on width
    float boxHeight = screenHeight * 0.96;      // x1   on height
    
    //Left Box
    LeftContext = {offsetX, offsetY, smallBoxWidth, boxHeight};
    DrawRectangleLinesEx(LeftContext, 2, WHITE);
    //todo topText, generateButton, "radio" checklist of algorythms
    DrawText("Generation:", offsetX * 2, offsetY * 2, offsetX*2, WHITE);

    string path = "./src/gen";
    for (const auto & entry : fs::directory_iterator(path)){
        string filename = entry.path().filename().string();
        filename = filename.substr(0, filename.size() - 4);

        //todo vector of buttons resize another loop diplay names n shit 
    }
    //Center Box
    CenterContext = {2 * offsetX + smallBoxWidth, offsetY, bigBoxWidth, boxHeight};
    DrawRectangleLinesEx(CenterContext, 2, WHITE);

    //Right Box
    RightContext = {screenWidth - (smallBoxWidth + offsetX), offsetY, smallBoxWidth, boxHeight};
    DrawRectangleLinesEx(RightContext, 2, WHITE);
}

void Gui::ChangeRectPosition(char c, float x, float y){
    switch (c){
    case 'l':
        this->LeftContext.x = x;
        this->LeftContext.y = y;
        break;
    case 'c':
        this->CenterContext.x = x;
        this->CenterContext.y = y;
        break;
    case 'r':
        this->RightContext.x = x;
        this->RightContext.y = y;
        break;
    }
}

Vector2 Gui::GetRectArea(char c){
    Vector2 point = {0};
    switch (c){
    case 'l':
        point.x = this->LeftContext.width;
        point.y = this->LeftContext.height;
        break;
    case 'c':
        point.x = this->CenterContext.width;
        point.y = this->CenterContext.height;
        break;
    case 'r':
        point.x = this->RightContext.width;
        point.y = this->RightContext.height;
        break;
    }
    return point;
}


