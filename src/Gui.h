#include <raylib.h>
class Gui {
    private:
        static Rectangle LeftContext;
        static Rectangle CenterContext;
        static Rectangle RightContext;
        struct Button{
            float posX;
            float posY;
            float width;
            float height;
            const char *text;
            Color buttonColor;
            Color textColor;
            void Display(){
                DrawRectangleRounded({posX, posY, width, height}, 2, 2, buttonColor);
                DrawText(text, posX + width / 2, posY + height / 2, 10, textColor);
            }
            void ChangeColor(Color buttonC, Color textC){
                buttonColor = buttonC;
                textColor = textC;
            }
        };
        
    public:
        static void Display();
        void ChangeRectPosition(char c, float x, float y);
        Vector2 GetRectArea(char c);
        // float GetRectPosX(char c[1]);
        // float GetRectPosY(char c[1]);
};