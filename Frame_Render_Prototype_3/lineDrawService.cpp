#include "lineDrawService.h"

#include <iostream>

// serviceHandle instance
LineDrawService* LineDrawService::serviceHandle = nullptr;

// Get the serviceHandle instance
LineDrawService* LineDrawService::getService() {
  return serviceHandle;
}

// Delete the serviceHandle instance
void LineDrawService::deleteService() {
  delete serviceHandle;
}

// Draw a horizontal line
void LineDrawService::drawHLine(unsigned lineLength) const {
  // Leaves the cursor directly to the right of the last character
  for (unsigned i = 0; i < lineLength; ++i) {
    std::cout << textgui_constants::thinLineChars[12];
  }
}

// Draw a vertical line
void LineDrawService::drawVLine(unsigned lineHeight) const {
  // Leaves the cursor right below the last character.
  for (unsigned i = 0; i < lineHeight; ++i) {
    std::cout << textgui_constants::thinLineChars[3]
              << "\033[1D\033[1B";
  }
}

// Draw a vertex
void LineDrawService::drawVertex(FrameVertex* targetVertex) const {
  unsigned vertexHash = hashIncomingEdges(targetVertex);
  std::cout << textgui_constants::thinLineChars[vertexHash];
}

//---------------------------
// Private Methods

// Get the hash key for the vertex
unsigned LineDrawService::hashIncomingEdges(FrameVertex* targetVertex) const {
  unsigned hashKey = 0;

  // b:lrtb
  if (targetVertex->getBottom()) {
    hashKey += 1;
  }

  if (targetVertex->getTop()) {
    hashKey += 2;
  }

  if (targetVertex->getRight()) {
    hashKey += 4;
  }

  if (targetVertex->getLeft()) {
    hashKey += 8;
  }

  return hashKey;
}
