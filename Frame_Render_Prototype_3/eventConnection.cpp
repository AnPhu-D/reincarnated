#include "eventConnection.h"
#include "event.h"

#include <iostream>

// Constructor for a function that takes in an Event* to handle
EventConnection::EventConnection(std::string _connectionID, std::function<void(Event*)> _connectedFunction) {
  connectionID = _connectionID;
  connectedFunction = _connectedFunction;
}

// Constructor for a function that takes in an Event* to handle and an object to call the function on
template <typename ObjType>
EventConnection::EventConnection(std::string _connectionID, void (ObjType::*func)(Event* hookedEvent), ObjType* obj) {
  connectionID = _connectionID;
  connectedFunction = [func, obj, this]() {
    (obj->*func)(this->hookedEvent);
  };
}

// Check if the connection is registered to an event
bool EventConnection::isRegistered() {
  return registered;
}

// Register the connection to an event
void EventConnection::registerConnection(Event* _hookedEvent) {
  hookedEvent = _hookedEvent;
  registered = true;
}

// Unregister the connection from an event
void EventConnection::unregisterConnection() {
  hookedEvent = nullptr;
  registered = false;
}

// Get the connectionID
std::string EventConnection::getID() const {
  return connectionID;
}

// Execute the function
void EventConnection::execute() const {
  connectedFunction(hookedEvent);
}