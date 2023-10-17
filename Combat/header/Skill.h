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
    Skill(std::string name, std::string description, double damage, int attackRange);
    void print();           // print the skill to the console in forms of "<name> description"
    std::string toString(); // return a string in the printing format
    double getDamage();
    int getAttackRange();
};

#endif // SKILL
