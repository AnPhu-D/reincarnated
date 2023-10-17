#include "highlightService.h"

#include <iostream>
#include <string>

// serviceHandle instance
HighlightService* HighlightService::serviceHandle = nullptr;

// Get the serviceHandle instance or create it if it doesn't exist
HighlightService* HighlightService::getService() {
  if (serviceHandle == nullptr) {
    serviceHandle = new HighlightService;
  }
  return serviceHandle;
}

// Delete the serviceHandle instance
void HighlightService::deleteService() {
  delete serviceHandle;
}

// Prep cursor for highlighting
void HighlightService::startHighlightColor(std::string targetColor) {
  if (targetColor == "none") {
    endHighlightColor();
  } else {
    std::cout << "\x1B[" + textgui_constants::bgColors.at(targetColor) + "m";
  }
}

// End cursor highlighting
void HighlightService::endHighlightColor() {
  std::cout << "\033[0m";
}