#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma once
#include <raylib.h>
#include <vector>
#include <cmath>
using std::vector;

class Gui {
    private:
        enum Context {
            LEFT,
            CENTER,
            RIGHT
        };
        int &mazeGridWidth;
        int &mazeGridHeight;
        void Init();
    public:
    
        void Display();
        Gui(int &gridHeight, int &gridWidth) : mazeGridWidth(gridWidth), mazeGridHeight(gridHeight) {
            Init();
        };

        enum Algorithm {
            //Gen
            None,
            Backtracking,
            HuntNKill,
            Prim,
            Kruskal,
            Eller,
            Sidewinder,
            Random,

            //Solve
            WallFollower,
            BreadthFirstSearch,
            DeadEndFiller,
            DepthFirstSearch,
            AStar,
            Tremaux
        };
        Algorithm choosenAlgorithm;

        double genTime = 0;
        int genIterations = 0;

        double solveTime = 0;
        int solveIterations = 0;

        bool ready = true;
        bool solveReady = false;
        Algorithm MainButtonHandler();

        void ChangeRectPosition(Context c, float x, float y);
        
        Vector2 GetRectArea(Context c);
        float GetRectPosX(Context c);
        float GetRectPosY(Context c);
    private:
        Rectangle LeftContext;
        Rectangle CenterContext;
        Rectangle RightContext;
        
        float offsetX;
        float offsetY;

        struct Button{
            float posX;
            float posY;
            float width;
            float height;

            const char *text;

            Algorithm alg;

            Color buttonColor = BLUE;
            Color textColor = WHITE;

            void Display(){
                DrawRectangleRounded({posX, posY, width, height}, 0.3, 3, buttonColor);
                float fontSize = height * 0.56f;
                DrawText(text, posX+width/2 - MeasureText(text, fontSize)/2, posY+height*0.26f, fontSize, textColor);
            }
            void DisplayRectangle(){
                DrawRectangle(posX, posY, width, height, buttonColor);
                float fontSize = height * 0.08f;
                DrawText(text, posX+width/2 - MeasureText(text, fontSize)/2, posY+height*0.26f, fontSize, textColor);
            }
            void ChangeColor(Color buttonC, Color textC){
                buttonColor = buttonC;
                textColor = textC;
            }
            bool IsHovered(){
                if((GetMouseX()>posX && GetMouseX()<posX+width) && (GetMouseY()>posY && GetMouseY()<posY+height)){
                        return true;
                }else{
                    return false;
                }
            }
            bool IsClicked(){
                if(IsHovered()){
                    if(IsMouseButtonPressed(0) || IsMouseButtonPressed(1)){
                        return true;
                    }
                }
                return false;
            }
        };
        
        vector<Button> genButtons;
        Button ChosenGen;
        Button StartGenButton;

        vector<Button> solveButtons;
        Button ChosenSolve;
        Button StartSolvingButton;

        Button MazeSettings;
};