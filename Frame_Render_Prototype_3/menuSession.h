#ifndef __MENUSESSION_H__
#define __MENUSESSION_H__

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "screenGui.h"
#include "screenRenderer.h"
#include "widget.h"
#include "widgetContext.h"

class MenuSession {
 public:
  // Constructor
  MenuSession(
      ScreenGUI* _sessionGUI,
      ScreenRenderer* _sessionRenderer,
      std::string _sessionID,
      std::function<void(Event*)> _onKeyPressFunction = [](Event*) -> void {});
  ~MenuSession();

  // Accessor
  std::string getSessionID() const;

  // Context Handlers
  void registerWidgetContext(WidgetContext* contextToRegister);
  WidgetContext* getCurrentWidgetContext() const;
  void setWidgetContext(unsigned widgetContextIndex);
  void nextContext();
  void prevContext();

  // Widget Handlers
  Widget* getCurrentWidget() const;
  void setWidget(unsigned widgetIndex);
  void nextWidget();
  void prevWidget();

  void setDefaultWidgetContext(unsigned widgetContextIndex);
  unsigned getDefaultWidgetContext() const;

  void activateCurrentWidget();

  // GUI Handlers
  void displayGUI() const;

  // Functionality
  void setUsesCustomKPF(bool KPFState);
  bool usesCustomKPF() const;

  // Defined  the same for all MenuSessions
  void defaultOnKeyPressFunction(Event* eventHandle);

 private:
  // Members
  std::string sessionID;

  ScreenGUI* sessionGUIHandle;
  ScreenRenderer* sessionRendererHandle;

  vector<WidgetContext*> widgetContexts;
  unsigned defaultWidgetContext = 0;

  bool useCustomOnKeyPressFunction = false;
  std::map<int, std::function<void(Event*)>> keyPressFunctionMap;

  std::function<void(Event*)> onKeyPressFunction;

  // State
  unsigned currentWidgetContext = 0;
  unsigned currentWidget = 0;

  // Internal Helpers
  const vector<Widget*>& getCurrentWidgetContextOrder() const;
};

#endif