#ifndef __COMBATINSTANCE_H__
#define __COMBATINSTANCE_H__

#include <map>
#include <string>
#include <vector>

#include "entity.h"
#include "party.h"

using std::vector;

enum TurnHolder {
  partyA,
  partyB
};

class CombatInstance {
 public:
  CombatInstance(Party* _partyA, Party* _partyB);
  ~CombatInstance();

  // Accessors
  const vector<Entity*>& getTurnOrder() const { return turnOrder; }
  const unsigned getTurnIndex() const { return turnIndex; }

  const Party& getPartyA() const { return *partyA; }
  const Party& getPartyB() const { return *partyB; }

  const unsigned getRoundNumber() const { return roundNumber; }
  const bool isATurn() const;
  const bool isOver();

  // Main Drivers
  void handleTurn();
  void handleTurn(unsigned skillIndex, vector<unsigned> targets);
  bool AWin;

 private:
  void generateTurnOrder();
  // Parties
  Party* partyA;  // Adds parties on construction
  Party* partyB;

  // Turn Tracking
  vector<Entity*> turnOrder;  // TODO: Find way to determine order
  unsigned turnIndex;
  unsigned roundNumber;

  // Other Tracking
  bool isInPartyA(unsigned) const;
  void removeDead();
};

#endif