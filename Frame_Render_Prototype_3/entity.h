#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <stdexcept>
#include <string>
#include <vector>

#include "attribute.h"
#include "role.h"
#include "skill.h"

using std::string;
using std::vector;

class Entity {
 public:
  // Constructor
  Entity(string _name);
  Entity(string _name, unsigned _totalHealth, int _defense, int _attack, vector<Skill*> _skills);
  ~Entity();

  // Member Manipulators
  string getName() const { return name; }
  Attribute* getHealthAttribute() const { return health; }
  Attribute* getStrengthAttribute() const { return strength; }
  unsigned getBuffedAttack() const;
  bool dead() const;

  unsigned getXP() const { return xp; }
  unsigned getMaxXP() const { return level * 100; }
  void addXP(unsigned xpToAdd);

  unsigned getLevel() const { return level; }
  void setLevel(unsigned _level);

  void useAttributePoint();

  const Role* getRole() const { return role; }
  void setRole(Role* _role);

  // Complex Manipulators
  void takeDamage(unsigned damage);
  Skill* getSkill(unsigned);
  unsigned getSkillSize();

 private:
  string name;
  Role* role;  // Aggregate, not Composing

  unsigned level = 1;
  unsigned xp = 0;
  unsigned attributePoints = 0;

  Attribute* health = nullptr;    // Composing
  Attribute* strength = nullptr;  // Composing
  vector<Skill*> skills;
};

#endif