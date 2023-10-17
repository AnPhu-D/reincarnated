
#include "DisplayHero.h"
DisplayHero::DisplayHero(GameManager *gameManager) : Component(gameManager, 5, 4)
{
    currentHero = 0;
    w = 113;
    h = 25;
}
void DisplayHero::keyEvent(char cha)
{
    removeFromScreen();
    if (cha == 67)
        currentHero = (currentHero + 1) % gameManager->myHeros.size();
    else if (cha == 68)
        currentHero = (currentHero - 1) % gameManager->myHeros.size();
}
void DisplayHero::render()
{
    _CursorService->moveCursor(5, 15);
    std::cout << "<<";
    _CursorService->moveCursor(115, 15);
    std::cout << ">>";
    _CursorService->moveCursor(70, 5);
    std::cout << gameManager->myHeros.at(currentHero)->getName();
    _CursorService->moveCursor(70, 10);
    std::cout << " attack: " << gameManager->myHeros.at(currentHero)->getAttack();
    _CursorService->moveCursor(70, 12);
    std::cout << " health: " << gameManager->myHeros.at(currentHero)->getTotalHealth();
    _CursorService->moveCursor(70, 14);
    std::cout << " defense: " << gameManager->myHeros.at(currentHero)->getDefense();
    _CursorService->moveCursor(70, 15);
    std::cout << " level: " << gameManager->myHeros.at(currentHero)->getLevel();
    _CursorService->moveCursor(10, 10);
    std::vector<std::vector<int>> ImageArray = gameManager->myHeros.at(currentHero)->image;
    for (int i = 0; i < ImageArray.size(); i++)
    {
        _CursorService->moveCursor(x + 20, y + i);
        for (int j = 0; j < ImageArray.at(0).size(); j++)
        {
            if (ImageArray[i][j] == 0)
                std::cout << "\033[1C";
            else
                std::cout << "\e[48;5;" << ImageArray[i][j] << "m" << char(32) << "\e[49m";
        }
    }
}
void DisplayHero::select() { return; }
void DisplayHero::unSelect() { return; }
DisplayHero::~DisplayHero()
{
}