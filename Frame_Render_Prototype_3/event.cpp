#include <exception>
#include <iostream>

#include "event.h"

Event::~Event() {
}

std::string Event::getID() const {
  return eventID;
}

// Execute all the functions that are binded to the event
void Event::fire() const {
  for (unsigned i = 0; i < eventConnections.size(); ++i) {
    EventConnection* iterEventConntection = eventConnections.at(i);
    iterEventConntection->execute();
  }
}

// Bind a function to the event
void Event::bindFunction(EventConnection* newEventConnection) {
  if (newEventConnection->isRegistered()) {
    throw std::runtime_error("Cannot register a connection to more than one event");
  }
  if (getFunction(newEventConnection->getID()) != nullptr) {
    throw std::runtime_error("Cannot have two connections with the same connectionID");
  }

  eventConnections.push_back(newEventConnection);
  newEventConnection->registerConnection(this);
}

// Remove a function from the event
void Event::unbindFunction(std::string eventConnectionID) {
  for (unsigned i = 0; i < eventConnections.size(); ++i) {
    if (eventConnections.at(i)->getID() == eventConnectionID) {
      eventConnections.at(i)->unregisterConnection();
      eventConnections.erase(eventConnections.begin() + i);
      break;
    }
  }
}

// Get a function from the event
EventConnection* Event::getFunction(std::string eventConnectionID) {
  for (unsigned i = 0; i < eventConnections.size(); ++i) {
    if (eventConnections.at(i)->getID() == eventConnectionID) {
      return eventConnections.at(i);
    }
  }
  return nullptr;
}