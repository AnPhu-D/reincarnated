#ifndef ENTITY_BANK
#define ENTITY_BANK

#include <iostream>
#include <string>
#include <vector>
#include "entity.h"
// #include "Bank.h"

#include "SkillBank.h"

class EntityBank {
 public:
  static EntityBank* getEntityBank() {
    if (_EntityBank == nullptr) {
      _EntityBank = new EntityBank;
    }
    return _EntityBank;
  }
  Entity* getEntity(unsigned i) {
    return (entities.at(i % entities.size()));
  }

  static void deleteBank() {
    delete _EntityBank;
  }

 private:
  static EntityBank* _EntityBank;

  EntityBank() {
    _EntityBank = this;
  }
  ~EntityBank() {
    for (unsigned i = 0; i < entities.size(); ++i) {
      delete entities.at(i);
    }
  }
  std::vector<Entity*> entities = {
      new Entity("Entity 1", 100, 1, 1, {SkillBank::getSkillBank()->getSkill(0), SkillBank::getSkillBank()->getSkill(2), SkillBank::getSkillBank()->getSkill(4)}),
      new Entity("Entity 2", 100, 2, 2, {SkillBank::getSkillBank()->getSkill(0), SkillBank::getSkillBank()->getSkill(2), SkillBank::getSkillBank()->getSkill(4), SkillBank::getSkillBank()->getSkill(5)}),
      new Entity("Entity 3", 100, 3, 3, {SkillBank::getSkillBank()->getSkill(4)}),
      new Entity("Entity 4", 100, 4, 4, {SkillBank::getSkillBank()->getSkill(6), SkillBank::getSkillBank()->getSkill(3)}),
      new Entity("Entity 5", 100, 5, 5, {SkillBank::getSkillBank()->getSkill(6), SkillBank::getSkillBank()->getSkill(3)}),
      new Entity("Entity 6", 100, 6, 6, {SkillBank::getSkillBank()->getSkill(6), SkillBank::getSkillBank()->getSkill(3)}),
      new Entity("Entity 7", 100, 7, 7, {SkillBank::getSkillBank()->getSkill(6), SkillBank::getSkillBank()->getSkill(3)}),
      new Entity("Entity 8", 100, 8, 8, {SkillBank::getSkillBank()->getSkill(6), SkillBank::getSkillBank()->getSkill(3)}),
  };
};

EntityBank* EntityBank::_EntityBank = nullptr;

#endif