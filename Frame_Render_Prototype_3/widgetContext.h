#ifndef __WIDGETCONTEXT_H__
#define __WIDGETCONTEXT_H__

#include <string>
#include <vector>

#include "widget.h"

class WidgetContext {
 public:
  void addWidget(Widget* widgetToAdd);
  const vector<Widget*>& getWidgetOrder() const;

  void assignSession(std::string newSessionID);
  bool hasSession() const;

 private:
  vector<Widget*> widgetOrder;
  std::string sessionID = "none";
};

#endif