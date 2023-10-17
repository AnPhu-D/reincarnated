#ifndef __PARTY_H__
#define __PARTY_H__

#include <string>
#include <vector>

#include "entity.h"

using std::string;
using std::vector;

class Party
{
public:
  // Constructor
  Party(unsigned _partySize);

  unsigned getPartySize() const { return partySize; }
  bool isFull() const;

  // Member Methods
  const vector<Entity *> &getPartyMembers() const { return partyMembers; }
  bool isMember(Entity *memberToCheck) const;
  void addMember(Entity *memberToAdd);
  void removeMember(Entity *memberToRemove);
  Entity *getPartyMember(unsigned index);

private:
  vector<Entity *> partyMembers; // Aggregates
  unsigned partySize;
};

#endif