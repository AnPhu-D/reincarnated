#include "menuSession.h"

// Constructor for a MenuSession, will handle interactions with the menu
MenuSession::MenuSession(
    ScreenGUI* _sessionGUI,
    ScreenRenderer* _sessionRenderer,
    std::string _sessionID,
    std::function<void(Event*)> _onKeyPressFunction) {
  sessionID = _sessionID;

  sessionGUIHandle = _sessionGUI;
  sessionRendererHandle = _sessionRenderer;

  onKeyPressFunction = _onKeyPressFunction;
  // If breaking because of params, implement using lambda:
  // map[index] = [this](Event*) { prevWidget(); };
  keyPressFunctionMap[119] = std::bind(&MenuSession::prevWidget, this);
  keyPressFunctionMap[115] = std::bind(&MenuSession::nextWidget, this);
  keyPressFunctionMap[97] = std::bind(&MenuSession::prevContext, this);
  keyPressFunctionMap[100] = std::bind(&MenuSession::nextContext, this);
}

// Clean up the MenuSession on destruction
MenuSession::~MenuSession() {
  delete sessionGUIHandle;
  for (unsigned i = 0; i < widgetContexts.size(); ++i) {
    delete widgetContexts.at(i);
  }
}

// Get the sessionID
std::string MenuSession::getSessionID() const {
  return sessionID;
}

// Add widgets through widgetContexts
void MenuSession::registerWidgetContext(WidgetContext* contextToRegister) {
  contextToRegister->assignSession(sessionID);
  widgetContexts.push_back(contextToRegister);
}

// Get what widgetContexts we are currently navigating
WidgetContext* MenuSession::getCurrentWidgetContext() const {
  return widgetContexts.at(currentWidgetContext);
}

// Get the order of widgets in the current widgetContext
const vector<Widget*>& MenuSession::getCurrentWidgetContextOrder() const {
  return getCurrentWidgetContext()->getWidgetOrder();
}

// Set what widgetContext we are navigating through
void MenuSession::setWidgetContext(unsigned widgetContextIndex) {
  unsigned maxContextIndex = widgetContexts.size() - 1;
  sessionRendererHandle->unhighlightWidget(getCurrentWidget());
  if (widgetContextIndex > maxContextIndex) {
    currentWidgetContext = maxContextIndex;
  } else {
    currentWidgetContext = widgetContextIndex;
  }
  sessionRendererHandle->highlightWidget(getCurrentWidget());
}

// Switch to the next widgetContext (horizontal navigation)
void MenuSession::nextContext() {
  if (widgetContexts.size() < 2) {
    return;
  }

  unsigned maxContextIndex = widgetContexts.size() - 1;
  if (maxContextIndex == currentWidgetContext) {
    return;
  } else {
    sessionRendererHandle->unhighlightWidget(getCurrentWidget());
    currentWidgetContext += 1;
  }

  currentWidget = 0;
  sessionRendererHandle->highlightWidget(getCurrentWidget());
}

// Switch to the previous widgetContext (horizontal navigation)
void MenuSession::prevContext() {
  if (widgetContexts.size() < 2) {
    return;
  }

  unsigned maxContextIndex = widgetContexts.size() - 1;
  if (currentWidgetContext == 0) {
    return;
  } else {
    sessionRendererHandle->unhighlightWidget(getCurrentWidget());
    currentWidgetContext -= 1;
  }

  currentWidget = 0;
  sessionRendererHandle->highlightWidget(getCurrentWidget());
}

// Set the default widgetContext
void MenuSession::setDefaultWidgetContext(unsigned widgetContextIndex) {
  defaultWidgetContext = widgetContextIndex;
}

// Get the default widgetContext
unsigned MenuSession::getDefaultWidgetContext() const {
  return defaultWidgetContext;
}

// Get the current widget we are highlighting
Widget* MenuSession::getCurrentWidget() const {
  return getCurrentWidgetContextOrder().at(currentWidget);
}

// Set the current widget we are highlighting
void MenuSession::setWidget(unsigned widgetIndex) {
  const vector<Widget*>& currentWidgetContextOrder = getCurrentWidgetContextOrder();
  unsigned maxWidgetIndex = currentWidgetContextOrder.size() - 1;
  sessionRendererHandle->unhighlightWidget(getCurrentWidget());
  if (widgetIndex > maxWidgetIndex) {
    currentWidget = maxWidgetIndex;
  } else {
    currentWidget = widgetIndex;
  }
  sessionRendererHandle->highlightWidget(getCurrentWidget());
}

// Switch to the next widget (vertical navigation)
void MenuSession::nextWidget() {
  const vector<Widget*>& currentWidgetContextOrder = getCurrentWidgetContextOrder();
  if (currentWidgetContextOrder.size() < 2) {
    CursorService::getService()->moveCursor(101, 17);
    std::cout << "   Debug: Returned because " << currentWidgetContextOrder.size() << " < "
              << "2";
    CursorService::getService()->moveCursor(101, 21);
    std::cout << "   " << currentWidget << " is CW, " << currentWidgetContext << "is CWC";
    return;
  }

  unsigned maxWidgetIndex = currentWidgetContextOrder.size() - 1;
  if (currentWidget == maxWidgetIndex) {
    CursorService::getService()->moveCursor(101, 17);
    std::cout << "   Debug: Returned because " << currentWidget << " = " << maxWidgetIndex;
    return;
  } else {
    sessionRendererHandle->unhighlightWidget(getCurrentWidget());
    currentWidget += 1;
  }

  sessionRendererHandle->highlightWidget(getCurrentWidget());
}

// Switch to the previous widget (vertical navigation)
void MenuSession::prevWidget() {
  const vector<Widget*>& currentWidgetContextOrder = getCurrentWidgetContextOrder();
  if (currentWidgetContextOrder.size() < 2) {
    return;
  }

  unsigned maxWidgetIndex = currentWidgetContextOrder.size() - 1;
  if (currentWidget == 0) {
    return;
  } else {
    sessionRendererHandle->unhighlightWidget(getCurrentWidget());
    currentWidget -= 1;
  }

  sessionRendererHandle->highlightWidget(getCurrentWidget());
}

// Establish the current widget as the active widget
void MenuSession::activateCurrentWidget() {
  Widget* currentWidget = getCurrentWidget();
}

// Show the GUI by getting the sessionRendererHandle to render the GUI
void MenuSession::displayGUI() const {
  const vector<Frame*> GUIFrames = sessionGUIHandle->getCreatedFrames();
  for (unsigned i = 0; i < GUIFrames.size(); ++i) {
    Frame* iterFrame = GUIFrames.at(i);
    if (!iterFrame->isVisible())
      return;
    sessionRendererHandle->renderFrame(GUIFrames.at(i));
  }
}

// Set whether a custom onKeyPressFunction is used
void MenuSession::setUsesCustomKPF(bool KPFState) {
  useCustomOnKeyPressFunction = KPFState;
}

// Check if the MenuSession uses a custom onKeyPressFunction
bool MenuSession::usesCustomKPF() const {
  return useCustomOnKeyPressFunction;
}

// The default function for handling keypresses
void MenuSession::defaultOnKeyPressFunction(Event* eventHandle) {
  KeyPressedEvent* keyPressedEventHandle = dynamic_cast<KeyPressedEvent*>(eventHandle);
  int keyCode = keyPressedEventHandle->getInputObject();

  auto it = keyPressFunctionMap.find(keyCode);
  if (it != keyPressFunctionMap.end()) {
    // Handle if found

    CursorService::getService()->moveCursor(101, 20);
    std::cout << "    Logging keypress " << keyCode << "   ";

    it->second(eventHandle);
  }
}
