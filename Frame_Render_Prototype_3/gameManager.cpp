#include "gameManager.h"

// Constructor

// Roles
Role* GameManager::getRole(string roleID) const {
  auto it = entityRoles.find(roleID);
  if (it != entityRoles.end()) {
    return it->second;
  } else {
    throw std::runtime_error("RoleID not found in entityRoles");
    return nullptr;
  }
}

bool GameManager::roleExists(string roleID) const {
  auto it = entityRoles.find(roleID);
  if (it != entityRoles.end()) {
    return true;
  } else {
    return false;
  }
}

void GameManager::addRole(string roleID, Role* roleToAdd) {
  if (roleExists(roleID)) {
    throw std::runtime_error("Role already exists");
  } else {
    entityRoles[roleID] = roleToAdd;
  }
}