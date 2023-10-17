#include "Entity.h"
#include "Skill.h"
#include <stdexcept>
#include <iostream>

Entity::Entity(std::string _name, int _totalHealth, int _defense, int _attack)
{
    name = _name;
    totalHealth = _totalHealth;
    currentHealth = _totalHealth;
    defense = _defense;
    attack = _attack;
    level = 1;
    XP = 0;
    skillList = std::vector<Skill *>();
}
Entity::Entity(std::string _name, int _totalHealth, int _defense, int _attack, std::vector<Skill *> skills)
{
    name = _name;
    totalHealth = _totalHealth;
    currentHealth = _totalHealth;
    defense = _defense;
    attack = _attack;
    level = 1;
    XP = 0;
    skillList = skills;
}

Entity::Entity()
{
    name = "No Name";
    totalHealth = 100;
    currentHealth = 100;
    defense = 100;
    attack = 5;
    level = 1;
    XP = 0;
    skillList = std::vector<Skill *>();
}
Entity::~Entity() {}
std::string Entity::getName()
{
    return name;
}
int Entity::getTotalHealth()
{
    return totalHealth;
}
int Entity::getCurrentHealth()
{
    return currentHealth;
}
int Entity::getAttack()
{
    return attack;
}
int Entity::getDefense()
{
    return defense;
}
int Entity::getLevel()
{
    return level;
}
int Entity::getXP()
{
    return XP;
}
void Entity::setLevel(int _level)
{
    level = _level;
}
void Entity::addLevel(int _level)
{
    level += _level;
}
void Entity::addXP(int _XP)
{
    XP += _XP;
    if (XP >= (level * 5 + 5))
    {
        XP = (level * 5 + 5) % XP;
        level++;
    }
}
Skill *Entity::getSkill(int index)
{
    if (index >= 4)
        throw std::out_of_range("skill list out of range");
    return skillList.at(index);
}
void Entity::takeDamage(int damage)
{
    currentHealth -= damage;
}
void Entity::addSkill(Skill *newSkill)
{
    if (skillList.size() == 4)
    {
        skillList.push_back(newSkill);
    }
}
void Entity::printEntity()
{
    std::cout << "Name: " << name << "  Lv." << level << std::endl;
    std::cout << currentHealth << "/" << totalHealth << std::endl;
}

void Entity::printEntityDetail()
{
    std::cout << "-------------------------Name: " << name << "  Lv." << level << "--------------------------------------" << std::endl;
    std::cout << currentHealth << "/" << totalHealth << std::endl;
    std::cout << "Defense: " << defense << std::endl;
    std::cout << "Attack: " << attack << std::endl;
    printSkills();
    std::cout << "-------------------------------------------------------" << std::endl;
}
void Entity::printSkills()
{
    std::cout << "---------------------------" << name << "skills-----------------" << std::endl;
    for (int i = 0; i < skillList.size(); i++)
    {
        std::cout << i << ": ";
        skillList.at(i)->print();
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------------------------" << std::endl;
}
bool Entity::ifDead()
{
    if (currentHealth <= 0)
        return true;
    return false;
}
int Entity::getskillSize()
{
    return skillList.size();
}
