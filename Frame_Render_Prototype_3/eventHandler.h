#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include <string>
#include <vector>

#include "event.h"

class EventHandler {
 public:
  unsigned cacheEvent(Event* eventToCache);
  void removeEvent(std::string eventID);

  Event* getEvent(unsigned eventCacheID) const;

 private:
  std::vector<Event*> cachedEvents;
};

#endif