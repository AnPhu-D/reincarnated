#include "highlightService.h"

#include <iostream>
#include <string>

HighlightService *HighlightService::serviceHandle = nullptr;

HighlightService *HighlightService::getService()
{
  return serviceHandle;
}

void HighlightService::startHighlightColor(std::string targetColor)
{
  if (targetColor == "none")
  {
    endHighlightColor();
  }
  else
  {
    std::cout << "\x1B[" + textgui_constants::bgColors.at(targetColor) + "m";
  }
}

void HighlightService::endHighlightColor()
{
  std::cout << "\033[0m";
}
