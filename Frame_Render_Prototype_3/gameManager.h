#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <algorithm>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "entity.h"
#include "role.h"
#include "combatInstance.h"

using std::map;
using std::string;
using std::vector;

class GameManager {
 public:
  // Constructor

  // Roles
  Role* getRole(string roleID) const;
  bool roleExists(string roleID) const;
  void addRole(string roleID, Role* roleToAdd);

 private:
  map<string, Role*> entityRoles;
};

#endif