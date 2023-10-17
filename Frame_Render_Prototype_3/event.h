#ifndef __EVENT_H__
#define __EVENT_H__

#include <functional>
#include <string>
#include <vector>

#include "eventConnection.h"

class EventConnection;

class Event {
 public:
  Event(std::string _eventID)
      : eventID(_eventID) {}
  virtual ~Event();

  std::string getID() const;

  virtual void fire() const;

  void bindFunction(EventConnection* newEventConnection);
  void unbindFunction(std::string eventConnectionID);

 private:
  std::string eventID;
  std::vector<EventConnection*> eventConnections;

  EventConnection* getFunction(std::string eventConnectionID);
};

#endif