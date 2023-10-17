
#ifndef DISPLAY_HERO
#define DISPLAY_HERO
#include "Component.h"
#include "GameManager.h"
#include <string>
#include <vector>

class DisplayHero : public Component
{
private:
    std::string name;
    int currentHero;

public:
    ~DisplayHero();
    DisplayHero(GameManager *);
    void keyEvent(char cha) override;
    void render() override;
    void select() override;
    void unSelect() override;
};

#endif // !DisplayHero
