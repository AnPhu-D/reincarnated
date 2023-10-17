#ifndef ENTITY
#define ENTITY

#include <string>
#include <vector>
#include "Skill.h"
#include "../../Items_And_Shops/armorItem.h"
#include "../../Items_And_Shops/weaponItem.h"

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
    ArmorItem armor;
    WeaponItem weapon;
    std::vector<Skill *> skillList;

public:
    std::vector<std::vector<int>> image; // the color code for this entity image
    // constructors
    Entity::Entity(std::string _name, int _totalHealth, int _defense, int _attack, std::vector<Skill *> skills);
    ~Entity();
    //  accessors
    std::string getName();
    int getTotalHealth();
    int getCurrentHealth();
    int getBuffredAttack(); // return the  attack buffed by the items and skill
    int getBuffedDefense(); // return the defense buffed by the items
    int getskillSize();     // return the number of skills an entity has, up to 4
    Skill *getSkill(int);   // return a specific skill by index
    //  modifiers
    void takeDamage(int);
    void addSkill(Skill *);
    // checkers
    bool ifDead();
};

#endif // ENTITY
