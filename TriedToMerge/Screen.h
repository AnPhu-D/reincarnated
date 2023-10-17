#ifndef SCREEN
#define SCREEN

#include <iostream>
#include <vector>
#include "Component.h"

class GameManager;
class Screen
{
private:
    std::vector<Component *> components;
    std::vector<Component *> eventComponents;
    GameManager *gameManager;

public:
    ~Screen();
    Screen(GameManager *);
    void render();
    void addEventComponents(Component *);
    void addComponent(Component *);
    void removeComponent(Component *);
    void removeComponent(int);
    void keyEvent(char);
    void navigateEvents(bool);
    int currentSelectedEvent;
    void clearScreen();
};

#endif // !SCREEN
