#include "entity.h"

Entity::Entity(string _name)
    : name(_name) {
  health = new Attribute(0, 0);
  strength = new Attribute(0, 0);
}
Entity::Entity(string _name, unsigned _totalHealth, int _defense, int _attack, std::vector<Skill*> _skills)
    : name(_name) {
  health = new Attribute(_totalHealth, _totalHealth);
  strength = new Attribute(100, _attack);
  skills = _skills;
}
Entity::~Entity() {
  delete health;
  delete strength;
}

void Entity::addXP(unsigned xpToAdd) {
  unsigned requiredXP = getMaxXP();
  unsigned newXP = xpToAdd + getXP();
  if (newXP >= requiredXP) {
    unsigned overflowXP = newXP - requiredXP;

    // Level up rewards
    level += 1;
    attributePoints += 3;

    xp = overflowXP;
  } else {
    xp = newXP;
  }
}

void Entity::setLevel(unsigned _level) {
  level = _level;
}

void Entity::useAttributePoint() {
  if (attributePoints == 0) {
    throw std::runtime_error("No remaining attribute points");
  }
  attributePoints -= 1;
}

void Entity::setRole(Role* _role) {
  role = _role;
}
Skill* Entity::getSkill(unsigned index) {
  return skills.at(index % skills.size());
}

unsigned Entity::getSkillSize() {
  return skills.size();
}
void Entity::takeDamage(unsigned damage) {
  health->removeValue(damage);
}
unsigned Entity::getBuffedAttack() const {  // need fix, right now it just returns the raw attack
  unsigned rawAttack = strength->getValue();
  return rawAttack;
}

bool Entity::dead() const {
  if (health->getValue() <= 0) {
    return true;
  }
  return false;
}
