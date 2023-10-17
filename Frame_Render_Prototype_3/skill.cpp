#include "skill.h"

Skill::Skill(std::string name, std::string description, double damage, int attackRange) : name(name), description(description), damage(damage), attackRange(attackRange) {}

unsigned Skill::getDamage() { return damage; }
int Skill::getAttackRange() { return attackRange; }

std::string Skill::getName() { return name; }
std::string Skill::getDescription() { return description; }
