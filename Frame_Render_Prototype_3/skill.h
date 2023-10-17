#ifndef SKILL
#define SKILL

#include <string>
#include <iostream>

class Skill
{
private:
    std::string name;
    std::string description;
    unsigned damage; // the percentage of damage add on the charactor's original damage
    int attackRange; // how many enemy can attack reach

public:
    Skill(std::string name, std::string description, double damage, int attackRange);
    unsigned getDamage();
    int getAttackRange();
    std::string getName();
    std::string getDescription();
};

#endif // SKILL
