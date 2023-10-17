#include "combatInstance.h"
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>
#include "party.h"

#include "services.h"

void wait(int milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

CombatInstance::CombatInstance(Party* _partyA, Party* _partyB) {
  partyA = _partyA;
  partyB = _partyB;
  generateTurnOrder();
  turnIndex = 0;
  roundNumber = 1;
}

CombatInstance::~CombatInstance() {}

void CombatInstance::generateTurnOrder() {
  turnOrder = vector<Entity*>();
  for (int i = 0; i < partyA->getPartySize(); i++) {
    turnOrder.push_back(partyA->getPartyMember(i));
  }
  for (int i = 0; i < partyB->getPartySize(); i++) {
    turnOrder.push_back(partyB->getPartyMember(i));
  }
}

// enemy turn
void CombatInstance::handleTurn() {
  if (isATurn())
    throw std::runtime_error("it is A's turn");
  Entity* attacker = turnOrder.at(turnIndex);

  Skill* skill = attacker->getSkill(rand() % attacker->getSkillSize());
  vector<unsigned> targets = vector<unsigned>();
  for (unsigned i = 0; i < turnOrder.size(); i++) {
    // fix later, for now it is just in order
    if (isInPartyA(i)) {
      targets.push_back(i);
    }
    if (targets.size() >= skill->getAttackRange())
      break;
  }
  // check if there's party A member in targets
  // for (unsigned i : targets)
  // {
  //     if (isInPartyA(i))
  //     {
  //         throw std::runtime_error("you cannot attack yourself");
  //     }
  // }
  for (unsigned i : targets) {
    Entity* target = turnOrder.at(turnIndex);
    target->takeDamage(attacker->getBuffedAttack());
  }
  removeDead();
  turnIndex = (turnIndex + 1) % turnOrder.size();
}
// my turn
void CombatInstance::handleTurn(unsigned skillIndex, vector<unsigned> targets) {
  Services::_CursorServiceHandle->moveCursor(101, 7);
  std::cout << "                                            " << std::flush;
  std::cout << "handleTurn Invoked" << std::flush;
  wait(500);
  std::cout << "                                            " << std::flush;

  if (!isATurn())
    throw std::runtime_error("it is not A's turn");
  Entity* attacker = turnOrder.at(turnIndex);
  Skill* skill = attacker->getSkill(skillIndex);
  if (skill->getAttackRange() < targets.size())
    throw std::runtime_error("target size exceed attack range");

  for (unsigned i : targets) {
    Entity* target = turnOrder.at(i);
    target->takeDamage(attacker->getBuffedAttack());

    Services::_CursorServiceHandle->moveCursor(101, 7);
    std::cout << target->getName() << " took " << attacker->getBuffedAttack() << " damage." << std::flush;
    wait(500);
    std::cout << "                                            " << std::flush;
  }
  removeDead();
  turnIndex = (turnIndex + 1) % turnOrder.size();
}
const bool CombatInstance::isATurn() const {
  if (isInPartyA(turnIndex))
    return true;
  return false;
}
bool CombatInstance::isInPartyA(unsigned index) const {
  if (partyA->isMember(turnOrder.at(index)))
    return true;
  return false;
}

void CombatInstance::removeDead() {
  for (int i = 0; i < turnOrder.size(); i++) {
    if (turnOrder.at(i)->dead()) {
      if (isInPartyA(i)) {
        partyA->removeMember(turnOrder.at(i));
      } else {
        partyB->removeMember(turnOrder.at(i));
      }
      turnOrder.erase(turnOrder.begin() + i);
      i--;
    }
  }
}
const bool CombatInstance::isOver() {
  if (partyA->getPartySize() <= 0) {
    AWin = true;
    return true;
  } else if (partyB->getPartySize() <= 0) {
    AWin = false;
    return true;
  }
  return false;
}