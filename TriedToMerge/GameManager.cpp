
// keydown from https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
#include <iostream>
#include <string>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>

#include "./GameManager.h"
#include "Screen.h"
#include "services.h"
#include "frameVertex.h"
#include "textgui_constants.h"
#include "slimeImageArray.h"
#include "flowerImageArray.h"

using Services::_CursorServiceHandle;
using Services::_HighlightServiceHandle;
using Services::_LineDrawServiceHandle;

bool GameManager::keydown()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    oldt.c_lflag &= ~ECHO;
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

GameManager::GameManager(int SCREEN_W, int SCREEN_H) : SCREEN_W(SCREEN_W), SCREEN_H(SCREEN_H)
{
    screens = std::vector<Screen *>();
    rerender = true;
    currentScreenIndex = ScreenIndice::START;
    allSkillList = std::vector<Skill *>();
    allEntities = std::vector<Entity *>();
    myHeros = std::vector<Entity *>();
    enemyTeam = new Team();
    myTeam = new Team();

    createSkillList();
    createEntityList();

    addHero(allEntities.at(1));
    addHero(allEntities.at(2));
    addHero(allEntities.at(3));
    addHero(allEntities.at(4));
    addHero(allEntities.at(5));
    // hard code the enemy team, it is gonna be the same for everylevel for now
    enemyTeam->addEntity(new Entity("Charactor 14", 9, 5, 8, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
    enemyTeam->addEntity(new Entity("Charactor 14", 9, 5, 8, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
    enemyTeam->addEntity(new Entity("Charactor 14", 9, 5, 8, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
    enemyTeam->addEntity(new Entity("Charactor 14", 9, 5, 8, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));

    _LineDrawServiceHandle->drawRect(SCREEN_W, SCREEN_H, 1, 1);
}
GameManager ::~GameManager()
{
    for (int i = 0; i < screens.size(); i++)
    {
        delete screens.at(i);
        screens.at(i) = nullptr;
    }
    for (int i = 0; i < allSkillList.size(); i++)
    {
        delete allSkillList.at(i);
        allSkillList.at(i) = nullptr;
    }
    for (int i = 0; i < allEntities.size(); i++)
    {
        delete allEntities.at(i);
        allEntities.at(i) = nullptr;
    }
    for (int i = 0; i < enemyTeam->entityList.size();i++){
        delete enemyTeam->entityList.at(i);
    }
        delete enemyTeam;
    delete myTeam;
}
void GameManager::render()
{
    if (!rerender)
        return;
    screens.at(currentScreenIndex)->render();
    rerender = false;
}
void GameManager::addScreen(Screen *screen)
{
    screens.push_back(screen);
}
void GameManager::removeScreen(Screen *) {}
void GameManager::removeScreen(int) {}
void GameManager::keyEvent(char cha)
{
    screens.at(currentScreenIndex)->keyEvent(cha);
    requestRender();
}
int GameManager::getScreenWidth() { return SCREEN_W; }
int GameManager::getScreenHeight() { return SCREEN_H; }
Screen *GameManager::getCurrentScreen()
{
    return screens.at(currentScreenIndex);
}
void GameManager::ScreenNavigate(std::string buttonText)
{
    screens.at(currentScreenIndex)->clearScreen();
    if (buttonText == "Start")
    {
        currentScreenIndex = ScreenIndice::MENU;
    }
    else if (buttonText == "Advendture")
    {
        currentScreenIndex = ScreenIndice::ADVENTURE;
    }
    else if (buttonText == "Back To Town")
    {
        currentScreenIndex = ScreenIndice::MENU;
    }
    else if (buttonText == "Guild")
    {
        currentScreenIndex = ScreenIndice::GUILD;
    }
    else if (buttonText.substr(0, 5) == "Level")
    {
        currentScreenIndex = ScreenIndice::SELECT;
    }
    else if (buttonText == "Battle")
    {
        currentScreenIndex = ScreenIndice::BATTLE;
    }
    else if (buttonText == "win")
    {
        currentScreenIndex = ScreenIndice::WIN;
    }
    else if (buttonText == "lose")
    {
        currentScreenIndex = ScreenIndice::LOSE;
    }
}

void GameManager::requestRender()
{
    rerender = true;
}
void GameManager::createEntityList()
{

    allEntities.push_back(new Entity("Charactor 1", 30, 5, 1, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 2", 30, 3, 2, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1)}, flowerImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 3", 30, 1, 3, {allSkillList.at(4), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 4", 30, 1, 2, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(5)}, flowerImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 5", 30, 5, 8, {allSkillList.at(5)}, slimeImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 6", 30, 5, 8, {allSkillList.at(4), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 7", 30, 5, 8, {allSkillList.at(0), allSkillList.at(1), allSkillList.at(3)}, flowerImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 8", 30, 5, 8, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(3)}, slimeImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 9", 30, 5, 8, {allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 10", 9, 5, 8, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, flowerImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 11", 9, 5, 8, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 12", 9, 5, 8, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 13", 9, 5, 8, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
    allEntities.push_back(new Entity("Charactor 14", 9, 5, 8, {allSkillList.at(0), allSkillList.at(2), allSkillList.at(1), allSkillList.at(3)}, slimeImageArray().ImageArray));
}

void GameManager::createSkillList()
{
    allSkillList.push_back(new Skill("Skill 1", "This can attat one charactor and add 50 percent damage", 0.5, 1));
    allSkillList.push_back(new Skill("Skill 2", "This can attat two charactor and add 40 damage", .4, 2));
    allSkillList.push_back(new Skill("Skill 3", "This can attat three charactor and add 30 damage", .3, 3));
    allSkillList.push_back(new Skill("Skill 4", "This can attat four charactor and add 10 damage", .1, 4));
    allSkillList.push_back(new Skill("Skill 5", "This can attat one charactor and add 10 damage", .1, 1));
    allSkillList.push_back(new Skill("Skill 6", "This can attat one charactor and add 10 damage", .1, 1));
    allSkillList.push_back(new Skill("Skill 7", "This can attat one charactor and add 10 damage", .1, 1));
    allSkillList.push_back(new Skill("Skill 8", "This can attat one charactor and add 10 damage", .1, 1));
    allSkillList.push_back(new Skill("Skill 9", "This can attat one charactor and add 10 damage", .1, 1));
    allSkillList.push_back(new Skill("Skill 10", "This can attat one charactor and add 10 damage", .1, 1));
}

void GameManager::addHero(Entity *hero)
{
    if (std::find(myHeros.begin(), myHeros.end(), hero) != myHeros.end())
    {
        std::cout << "duplicates" << std::endl;
        return;
    }
    myHeros.push_back(hero);
}