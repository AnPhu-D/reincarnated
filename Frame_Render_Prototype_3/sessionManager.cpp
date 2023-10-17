#include "sessionManager.h"

// Constructor
SessionManager::SessionManager() {
  gameRenderService = new ScreenRenderer;
}

// Destructor
SessionManager::~SessionManager() {
  delete gameRenderService;

  for (auto it = sessionLookup.begin(); it != sessionLookup.end(); ++it) {
    delete it->second;
  }
}

// Accessors
ScreenRenderer* SessionManager::getRenderer() const {
  return gameRenderService;
}

// Session Management
bool SessionManager::foundSession(std::string sessionID) const {
  auto it = sessionLookup.find(sessionID);
  return it != sessionLookup.end();
}

// Get the session with the given sessionID
MenuSession* SessionManager::getSession(std::string sessionID) const {
  auto it = sessionLookup.find(sessionID);
  if (it != sessionLookup.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}

// Create a session
void SessionManager::addSession(MenuSession* sessionToAdd, std::string sessionID) {
  // Prevent duplicate keys
  if (foundSession(sessionID)) {
    throw std::runtime_error("Cannot add two sessions with the same sessionID");
  }

  sessionLookup[sessionID] = sessionToAdd;
}

// Remove a session
void SessionManager::removeSession(std::string sessionID) {
  if (foundSession(sessionID) == false) {
    return;
  }

  // Remove the session. Does it need to clean itself up
  // or does the manager clean it up?
  throw std::runtime_error("FixMe! : SessionManager::removeSession()");
}

// Get the current session
MenuSession* SessionManager::getCurrentSession() const {
  return currentSession;
}

// Set the current session
void SessionManager::setCurrentSession(std::string sessionID) {
  if (foundSession(sessionID) == false) {
    throw std::runtime_error("Tried to select nonexistant session");
  }

  currentSession = sessionLookup[sessionID];
}

// Cleanup the current session
void SessionManager::cleanupCurrentSession() const {
  gameRenderService->clearScreen();
}

// Switch sessions
void SessionManager::transitionToSession(std::string targetSessionID) {
  MenuSession* targetSession = getSession(targetSessionID);
  cleanupCurrentSession();
  setCurrentSession(targetSession->getSessionID());

  // Draw the menu
  targetSession->displayGUI();

  // Reset selection contexts
  targetSession->setWidgetContext(targetSession->getDefaultWidgetContext());
  targetSession->setWidget(0);

  gameRenderService->highlightWidget(targetSession->getCurrentWidget());
  Services::_CursorServiceHandle->moveCursor(101, 25);
}

// Input
void SessionManager::parseKeyPress(Event* eventHandle) {
  if (getCurrentSession() == nullptr) {
    throw std::runtime_error("No session selected");
  }

  KeyPressedEvent* keyPressedEventHandle = dynamic_cast<KeyPressedEvent*>(eventHandle);
  int keyCode = keyPressedEventHandle->getInputObject();

  CursorService::getService()->moveCursor(101, 24);
  std::cout << "   " << keyCode << "   ";

  // Intercept special widget interactions before they go to the MenuSession
  Widget* currentWidget = currentSession->getCurrentWidget();

  // Intercept special keycodes before they go to the MenuSession
  if (keyCode == 10 || keyCode == 13) {
    // 10 or 13 is return/carriage return (enter)
    bool canPressButton = currentWidget->canPressButton();
    if (!canPressButton) {
      return;
    }

    currentWidget->onButtonPress();
    return;
  }

  if (currentSession->usesCustomKPF() == false) {
    currentSession->defaultOnKeyPressFunction(eventHandle);
  } else if (currentSession->usesCustomKPF() == true) {
    throw std::runtime_error("FixMe: SessionParseKeyPress");
  } else {
    throw std::logic_error("Reached unexpected branch in parseKeyPress()");
  }
}