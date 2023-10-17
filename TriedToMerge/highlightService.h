#ifndef __HIGHIGHTSERVICE_H__
#define __HIGHIGHTSERVICE_H__

#include <iostream>
#include <string>

#include "frameVertex.h"
#include "textgui_constants.h"

class HighlightService
{
public:
  // Service Handle
  static HighlightService *getService();

  // Delete the copy and assignment constructors
  HighlightService(const HighlightService &) = delete;
  HighlightService &operator=(const HighlightService &) = delete;

  // Service Methods
  void startHighlightColor(std::string targetColor);
  void endHighlightColor();

private:
  static HighlightService *serviceHandle;

  HighlightService()
  {
    serviceHandle = this;
  }
  ~HighlightService() {}

  // Service Internal Methods
};

#endif