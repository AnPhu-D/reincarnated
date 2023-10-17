#include <stdexcept>

#include "widgetContext.h"

// Add a widget to the context
void WidgetContext::addWidget(Widget* widgetToadd) {
  widgetOrder.push_back(widgetToadd);
}

// Get the order of widgets in the context
const vector<Widget*>& WidgetContext::getWidgetOrder() const {
  return widgetOrder;
}

// Check whether the context is assigned to a session
bool WidgetContext::hasSession() const {
  return sessionID != "none";
}

// Assign the context to a session
void WidgetContext::assignSession(std::string newSessionID) {
  if (hasSession()) {
    throw std::runtime_error("Cannot assign a context to two sessions");
  }
  sessionID = newSessionID;
}