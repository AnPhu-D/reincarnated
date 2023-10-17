#ifndef __ROLE_H__
#define __ROLE_H__

#include <algorithm>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Role {
 public:
  Role(const vector<string>& _validArmorTypes, const vector<string>& _validWeaponTypes)
      : validArmorTypes(_validArmorTypes), validWeaponTypes(_validWeaponTypes) {}

  const vector<string>& getValidArmorTypes() const { return validArmorTypes; }
  const vector<string>& getValidWeaponTypes() const { return validWeaponTypes; }

  bool armorValid(string armorType) const;
  bool weaponValid(string weaponType) const;

 private:
  vector<string> validArmorTypes;
  vector<string> validWeaponTypes;
};

#endif