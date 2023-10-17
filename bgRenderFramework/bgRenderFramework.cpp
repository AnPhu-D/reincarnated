// keydown from https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
#include <iostream>
#include <string>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// using std::cin;
// using std::cout;
// using std::string;
char SPACE = 32;
using namespace std;

class bgRenderFramework
{

private:
    string clear = "\e[49m";
    void moveUp(int pos)
    {
        cout << "\033[" << pos << "A";
    }
    void moveDown(int pos)
    {
        cout << "\033[" << pos << "B";
    }
    void moveleft(int pos)
    {
        cout << "\033[" << pos << "D";
    }
    void moveright(int pos)
    {
        cout << "\033[" << pos << "C";
    }
    void backToOrigin()
    {
        cout << "\033[u";
    }

public:
    int screen_width = 0;
    int screen_height = 0;
    bgRenderFramework(int w, int h)
    {
        screen_height = h;
        screen_width = w;
        cout << "\033[s";
    }
    void drawHorizontalLine(int length, int color, int x, int y)
    {
        cout << "\033[u";
        moveDown(y);
        moveright(x);
        for (int i = 0; i < length; i++)
        {
            cout << "\e[48;5;" << color << "m" << SPACE << clear;
        }
    }
    void drawVerticalLine(int length, int color, int x, int y)
    {
        cout << "\033[u";
        moveDown(y);
        moveright(x);
        for (int i = 0; i < length; i++)
        {
            cout << "\e[48;5;" << color << "m" << SPACE << clear;
            moveDown(1);
            moveleft(1);
        }
        cout << "\033[u";
    }
    void drawRectangle(int width, int height, int color, int x, int y)
    {
        cout << "\033[u";
        moveDown(y);
        moveright(x);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                cout << "\e[48;5;" << color << "m" << SPACE << clear;
            }
            moveDown(1);
            moveleft(width);
        }
        cout << "\033[u";
    }
    void drawPicture(int width, int height, vector<vector<int>> color, int x, int y)
    {

        cout << "\033[u";
        moveDown(y);
        moveright(x);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (color[i][j] == 0)
                    cout << "\033[1C";
                else
                    cout << "\e[48;5;" << color[i][j] << "m" << SPACE << clear;
            }
            moveDown(1);
            moveleft(width);
        }
        cout << "\033[u";
    }
    void fillScreen(int color)
    {
        drawRectangle(screen_width, screen_height, color, 0, 0);
    }
};
bool keydown()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
// int main()
// {
//     bgRenderFramework bgRenderFramework(80,30);
//     char input;
//     while (1)
//     {
//         if(keydown())
//         {
//             if(getchar() == '1')
//                 bgRenderFramework.drawRectangle(5, 4, 34, 6, 7);
//         else
//         {
//             bgRenderFramework.drawHorizontalLine(5, 56, 6, 7);
//             bgRenderFramework.drawVerticalLine(5, 64, 6, 7);}

//         }
//         bgRenderFramework.fillScreen(234);
//         // cout<<"hi";
//     }
//     // bgRenderFramework.drawHorizontalLine(5, 34, 6, 7);
//     // bgRenderFramework.drawVerticalLine(5, 34, 6, 7);
//     return 0;
// }