#ifndef SKILL_BANK
#define SKILL_BANK

#include <iostream>
#include <string>
#include <vector>
#include "skill.h"

class SkillBank {
 public:
  static SkillBank* getSkillBank() {
    if (_SkillBank == nullptr) {
      _SkillBank = new SkillBank;
    }
    return _SkillBank;
  }
  Skill* getSkill(unsigned i) {
    return (skills.at(i % skills.size()));
  }

  static void deleteBank() {
    delete _SkillBank;
  }

 private:
  static SkillBank*
      _SkillBank;

  SkillBank() {
    _SkillBank = this;
  }
  ~SkillBank() {
    for (unsigned i = 0; i < skills.size(); ++i) {
      delete skills.at(i);
    }
  }
  std::vector<Skill*> skills = {
      new Skill("skill 1", "this is skill 1", 1, 1),
      new Skill("skill 2", "this is skill 2", 2, 2),
      new Skill("skill 3", "this is skill 3", 3, 3),
      new Skill("skill 4", "this is skill 4", 4, 4),
      new Skill("skill 5", "this is skill 5", 5, 5),
      new Skill("skill 6", "this is skill 6", 6, 6),
      new Skill("skill 7", "this is skill 7", 7, 7),
      new Skill("skill 8", "this is skill 8", 8, 8),
  };
};

SkillBank* SkillBank::_SkillBank = nullptr;

#endif