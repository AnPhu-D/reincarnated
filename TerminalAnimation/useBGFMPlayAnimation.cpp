// ANSI / VT100 Terminal Control Escape Sequences:https://web.archive.org/web/20151004211730/http://www.termsys.demon.co.uk/vtansi.htm
#include <iostream>
#include "SlimeanimationArray.h"
#include "MushroomanimationArray.h"
#include "FloweranimationArray.h"
#include "AmongUsanimationArray.h"
#include "../bgRenderFramework/bgRenderFramework.cpp"
#include <bits/stdc++.h>

float TICK = 0;

// using namespace std;

// enum Code
// {
//     RED = 31,
//     GREEN = 32,
//     BLUE = 34,
//     DEFAULT = 39,
//     RED_BG = 41,
//     GREEN_BG = 42,
//     BLUE_BG = 44,
//     DEFAULT_BG = 49
// };
char BLOCK = 178;
char DEFAULT_BG = 49;
// char SPACE = 32;

void playAnimation(animation ani)
{
    int frame = 0;
    // animation[0][0][0] = 255;
    while (true)
    {
        for (int y = 0; y < ani.height; y++)
        {
            for (int x = 0; x < ani.width; x++)
            {
                if (ani.animationArray[frame][y][x] == 0)
                {
                    cout << "\e[" << DEFAULT_BG << "m" << SPACE;
                }
                else
                {
                    cout << "\e[48;5;" << ani.animationArray[frame][y][x] << "m" << SPACE;
                }
            }
            cout << "\e[" << DEFAULT_BG << "m"
                 << "\n";
        }

        frame = (frame + 1) % ani.frameNum;
        cout << "\e[" << ani.width << "D";
        cout << "\e[" << ani.height << "A";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << std::flush;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int select;
    cout << "which animation you want to play: 1. Slime, 2. Flower, 3. Mushroom, 4.Amongus" << std::endl;
    cin >> select;
    animation ani;
    switch (select)
    {
    case 1:
        ani = Slime();
        break;
    case 2:
        ani = Flower();
        break;
    case 3:
        ani = Mushroom();
        break;
    case 4:
        ani = AmongUs();
        break;
    }
    bgRenderFramework fw(60, 30);
    while (1)
    {
        TICK += 1;
        fw.fillScreen(135);
        fw.drawPicture(ani.width, ani.height, ani.animationArray[(int)TICK % ani.frameNum], 0, 0);
        // playAnimation(ani);
    }
    return 0;
}
