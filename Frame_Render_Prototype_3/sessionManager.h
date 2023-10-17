#ifndef __SESSIONMANAGER_H__
#define __SESSIONMANAGER_H__

#include <map>
#include <string>
#include <vector>

#include "menuSession.h"
#include "screenRenderer.h"
#include "widget.h"

class SessionManager {
 public:
  // Constructor
  SessionManager();
  ~SessionManager();

  // Accessors
  ScreenRenderer* getRenderer() const;

  // Session Management
  bool foundSession(std::string sessionID) const;
  MenuSession* getSession(std::string sessionID) const;

  void addSession(MenuSession* sessionToAdd, std::string sessionID);
  void removeSession(std::string sessionID);

  MenuSession* getCurrentSession() const;
  void setCurrentSession(std::string sessionID);

  // Cleanup
  void cleanupCurrentSession() const;
  void transitionToSession(std::string targetSessionID);

  // Input
  void parseKeyPress(Event* eventHandle);

 private:
  // Service Handles
  ScreenRenderer* gameRenderService = nullptr;

  // Members
  MenuSession* currentSession = nullptr;
  std::map<std::string, MenuSession*> sessionLookup;
};

#endif