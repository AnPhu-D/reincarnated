#include "cursorService.h"

CursorService* CursorService::serviceHandle = nullptr;

CursorService* CursorService::getService() {
  return serviceHandle;
}

void CursorService::deleteService() {
  delete serviceHandle;
}

void CursorService::moveCursor(unsigned newX, unsigned newY) {
  std::cout << "\033[" << std::to_string(newY) << ";" << std::to_string(newX) << "H";
}
