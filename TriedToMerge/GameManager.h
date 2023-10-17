#ifndef GAMEMANAGER
#define GAMEMANAGER

#include <iostream>
#include <vector>
#include "Entity.h"
#include "Skill.h"
#include "Team.h"

class Screen;
enum ScreenIndice
{
    START = 0,
    MENU = 1,
    ADVENTURE = 2,
    GUILD = 3,
    SELECT = 4,
    BATTLE = 5,
    WIN = 6,
    LOSE = 7,

};

class GameManager
{
private:
    std::vector<Screen *> screens;
    int SCREEN_W;
    int SCREEN_H;
    bool rerender;
    void createEntityList();
    void createSkillList();
    ScreenIndice currentScreenIndex;

public:
    void requestRender();
    ~GameManager();
    GameManager(int, int);
    void render();
    void addScreen(Screen *);
    void removeScreen(Screen *);
    void removeScreen(int);
    void keyEvent(char);
    int getScreenWidth();
    int getScreenHeight();
    bool keydown();
    Screen *getCurrentScreen();
    void ScreenNavigate(std::string);
    std::vector<Skill *> allSkillList;
    std::vector<Entity *> allEntities;
    std::vector<Entity *> myHeros;
    void addHero(Entity *);
    Team *myTeam;
    Team *enemyTeam;
};

#endif // !GameManager
