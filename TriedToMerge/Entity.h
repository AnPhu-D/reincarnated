#ifndef ENTITY
#define ENTITY

#include <string>
#include "Skill.h"
#include <vector>

class Entity
{
private:
    std::string name;
    int totalHealth;
    int currentHealth;
    int defense;
    int attack;
    int level;
    int XP;

public:
    std::vector<std::vector<int>> image;
    std::vector<Skill *> skillList;
    // constructors
    Entity();
    Entity(std::string, int, int, int);
    Entity(std::string, int, int, int, std::vector<Skill *>, std::vector<std::vector<int>>);
    ~Entity();
    //  accessors
    std::string getName();
    int getTotalHealth();
    int getCurrentHealth();
    int getAttack();
    int getDefense();
    int getLevel();
    int getXP();
    int getskillSize();
    Skill *getSkill(int);
    //  modifiers
    void addLevel(int);
    void setLevel(int);
    void addXP(int);
    void takeDamage(int);
    void addSkill(Skill *);
    // printers
    void printEntity();
    void printEntityDetail();
    void printSkills();
    // checkers
    bool ifDead();
};

#endif // ENTITY
