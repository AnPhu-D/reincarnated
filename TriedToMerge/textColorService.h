#ifndef __TEXTCOLORSERVICE_H__
#define __TEXTCOLORSERVICE_H__

#include <iostream>
#include "textgui_constants.h"

class TextColorService {
 public:
  // Service Handle
  static TextColorService* getService();

  // Delete the copy and assignment constructors
  TextColorService(const TextColorService&) = delete;
  TextColorService& operator=(const TextColorService&) = delete;

  // Service Methods
  void startTextColor(std::string targetColor);
  void endTextColor();

 private:
  static TextColorService* serviceHandle;

  TextColorService() {
    serviceHandle = this;
  }
  ~TextColorService() {}
};

#endif