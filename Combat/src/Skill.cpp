#include "Skill.h"

Skill::Skill(std::string name, std::string description, double damage, int attackRange) : name(name), description(description), damage(damage), attackRange(attackRange) {}
void Skill::print()
{
    std::cout << name << " " << description;
}
double Skill::getDamage() { return damage; }
int Skill::getAttackRange() { return attackRange; }
