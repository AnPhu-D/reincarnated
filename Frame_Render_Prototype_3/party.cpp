#include "party.h"

Party::Party(unsigned _partySize)
{
  partySize = _partySize;
}

bool Party::isFull() const
{
  return partyMembers.size() >= partySize;
}

bool Party::isMember(Entity *memberToCheck) const
{
  auto it = partyMembers.begin();
  while (it != partyMembers.end())
  {
    if (*it == memberToCheck)
    {
      return true;
    }
    ++it;
  }
  return false;
}

void Party::addMember(Entity *memberToAdd)
{
  if (isMember(memberToAdd))
  {
    return;
  }
  partyMembers.push_back(memberToAdd);
}

void Party::removeMember(Entity *memberToRemove)
{
  auto it = partyMembers.begin();
  while (it != partyMembers.end())
  {
    if (*it == memberToRemove)
    {
      partyMembers.erase(it);
    }
    ++it;
  }
}
Entity *Party::getPartyMember(unsigned index)
{
  return partyMembers.at(index % partyMembers.size());
}