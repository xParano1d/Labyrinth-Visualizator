#include <vector>
#include <raylib.h>
using std::vector;
class Grid {
    private:
        int rows;
        int columns;
        struct Cell{
            bool rightWall;
            bool leftWall;
            bool topWall;
            bool bottomWall;
            Color color;
        };
        vector<vector<Cell>> grid;
    public:
        void Create(int rows, int columns);
        void Display(float posX, float posY, float width, float height);
};