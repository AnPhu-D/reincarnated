#include <iostream>
#include "SelectTeam.h"
#include "GameManager.h"

void SelectTeam::keyEvent(char cha)
{
    if (cha >= 49 and cha <= 57)
    {
        if ((int)cha - 49 >= selectArray.size())
            return;
        if (selectArray.at((int)cha - 49))
        {
            selectArray.at((int)cha - 49) = false;
        }
        else
        {
            if (countSelected() < 4)
            {

                selectArray.at((int)cha - 49) = true;
                ;
            }
        }
    }
    if (cha == 10)
    {
        if (countSelected() != 4)
            return;
        delete gameManager->myTeam;
        gameManager->myTeam = new Team();

        for (int i = 0; i < selectArray.size(); i++)
        {
            if (selectArray.at(i))
            {
                gameManager->myTeam->addEntity(gameManager->myHeros.at(i));
            }
        }

        gameManager->ScreenNavigate("Battle");
    }
}
SelectTeam::SelectTeam(GameManager *gameManager, int _x, int _y) : Component(gameManager, _x, _y)
{
    w = 100;
    h = 18;
    selectArray = std::vector<bool>();
    for (int i = 0; i < gameManager->myHeros.size(); i++)
    {
        selectArray.push_back(false);
    }
}
void SelectTeam::render()
{
    _CursorService->moveCursor(5, 5);
    std::cout << "press number to select heros, and you can press the number again to unselect the hero.";
    _CursorService->moveCursor(5, 6);
    std::cout << "Make sure that you select 4 herors and then press ENTER to enter the combat.";
    for (int i = 0; i < gameManager->myHeros.size(); i++)
    {
        _CursorService->moveCursor(10, 10 + i);
        printHero(i);
    }
}
void SelectTeam::select()
{
    return;
}
void SelectTeam::unSelect()
{
    return;
}
void SelectTeam::printHero(int index)
{
    if (selectArray.at(index))
    {
        _HighlightService->startHighlightColor("Red");
    }
    std::cout << "#" << index + 1 << " ";
    gameManager->myHeros.at(index)->printEntityDetail();
    _HighlightService->endHighlightColor();
}
int SelectTeam::countSelected()
{
    int count = 0;
    for (int i = 0; i < selectArray.size(); i++)
    {
        if (selectArray.at(i))
        {
            count++;
        }
    }
    return count;
}
