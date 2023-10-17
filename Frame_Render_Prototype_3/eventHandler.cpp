#include "eventHandler.h"

// Add an event to the EventHandler and return its cacheID
unsigned EventHandler::cacheEvent(Event* eventToCache) {
  unsigned eventCacheID = cachedEvents.size();
  cachedEvents.push_back(eventToCache);
  return eventCacheID;
}

// Remove an event from the EventHandler
void EventHandler::removeEvent(std::string eventID) {
  for (unsigned i = 0; i < cachedEvents.size(); ++i) {
    if (cachedEvents.at(i)->getID() == eventID) {
      cachedEvents.erase(cachedEvents.begin() + i);
      break;
    }
  }
}

// Get an event from the EventHandler
Event* EventHandler::getEvent(unsigned eventCacheID) const {
  return cachedEvents.at(eventCacheID);
}