#ifndef __EVENTCONNECTION_H__
#define __EVENTCONNECTION_H__

#include <functional>
#include <string>

#include "event.h"

class Event;

class EventConnection {
 public:
  // Usage: Check pins in `100 FrontEnd implementation` group chat
  EventConnection(std::string _connectionID, std::function<void(Event*)> _connectedFunction);

  // Usage: EventConnection(&MyObject::myObjectFunction, &obj);
  template <typename ObjType>
  EventConnection(std::string _connectionID, void (ObjType::*func)(Event*), ObjType* obj);

  bool isRegistered();
  void registerConnection(Event* _hookedEvent);
  void unregisterConnection();

  std::string getID() const;
  void execute() const;

 private:
  std::string connectionID;
  std::function<void(Event*)> connectedFunction;
  Event* hookedEvent;

  bool registered = false;
};

#endif