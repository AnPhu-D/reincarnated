#include "textColorService.h"

#include <iostream>
#include <string>
#include "textgui_constants.h"

TextColorService* TextColorService::serviceHandle = nullptr;

TextColorService* TextColorService::getService() {
  return serviceHandle;
}

void TextColorService::startTextColor(std::string targetColor) {
  std::cout << "\x1B[" + textgui_constants::fgColors.at(targetColor) + "m";
}

void TextColorService::endTextColor() {
  std::cout << "\033[0m";
}

//---------------------------
// Private Methods