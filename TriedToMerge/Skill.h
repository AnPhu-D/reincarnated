#if !defined(SKILL)
#define SKILL

#include <string>
#include <iostream>

class Skill
{
private:
    std::string name;
    std::string description;
    double damage;   // the percentage of damage add on the charactor's original damage
    int attackRange; // how many enemy can attack reach

public:
    Skill(std::string name, std::string description, double damage, int attackRange) : name(name), description(description), damage(damage), attackRange(attackRange) {}
    void print()
    {
        std::cout << name << " " << description;
    }
    double getDamage() { return damage; }
    int getAttackRange() { return attackRange; }
};

#endif // SKILL
