#include "Screen.h"
#include "GameManager.h"
void Screen::render()
{
    for (Component *component : components)
    {
        component->render();
    }
    for (Component *component : eventComponents)
    {
        component->render();
    }
}

void Screen::addComponent(Component *component)
{
    components.push_back(component);
}
void Screen::addEventComponents(Component *component)
{
    eventComponents.push_back(component);
}
void Screen::removeComponent(Component *component)
{

    for (std::vector<Component *>::iterator iter = components.begin(); iter < components.end(); iter++)
    {
        if (*iter == component)
        {
            components.erase(iter);
            return;
        }
    }
    std::cout << "FIX:add exception, component not found" << std::endl;
}
void Screen::removeComponent(int index)
{
    if (index < 0 or index > components.size())
    {
        std::cout << "FIX:add exception, index out of bound" << std::endl;
        return;
    }
    components.erase(components.begin() + index);
}
void Screen::keyEvent(char cha)
{
    if (cha == 67)
    {
        navigateEvents(true);
    }
    else if (cha == 68)
    {
        navigateEvents(false);
    }
    for (Component *component : eventComponents)
    {
        component->keyEvent(cha);
    }
}

Screen::Screen(GameManager *_gameManager) : gameManager(_gameManager)
{
    components = std::vector<Component *>();
    eventComponents = std::vector<Component *>();
    currentSelectedEvent = 0;
};
void Screen::navigateEvents(bool right)
{
    eventComponents.at(currentSelectedEvent)->unSelect();
    if (right)
    {
        currentSelectedEvent = (currentSelectedEvent + 1) % eventComponents.size();
    }
    else
    {
        if (currentSelectedEvent == 0)
        {
            currentSelectedEvent = eventComponents.size() - 1;
        }
        else
            currentSelectedEvent = (currentSelectedEvent - 1) % eventComponents.size();
    }
    eventComponents.at(currentSelectedEvent)->select();
}

void Screen::clearScreen()
{
    for (Component *component : components)
    {
        component->removeFromScreen();
    }

    for (Component *component : eventComponents)
    {
        component->removeFromScreen();
    }
}
Screen::~Screen()
{
    for (int i = 0; i < components.size(); i++)
    {
        delete components.at(i);
        components.at(i) = nullptr;
    }
    for (int i = 0; i < eventComponents.size(); i++)
    {
        delete eventComponents.at(i);
        eventComponents.at(i) = nullptr;
    }
}