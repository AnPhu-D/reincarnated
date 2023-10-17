#include "lineDrawService.h"

#include <iostream>

LineDrawService *LineDrawService::serviceHandle = nullptr;

LineDrawService *LineDrawService::getService()
{
  return serviceHandle;
}

void LineDrawService::drawHLine(unsigned lineLength) const
{
  // Leaves the cursor directly to the right of the last character
  for (unsigned i = 0; i < lineLength; ++i)
  {
    std::cout << textgui_constants::thinLineChars[12];
  }
}

void LineDrawService::drawVLine(unsigned lineHeight) const
{
  // Leaves the cursor right below the last character.
  for (unsigned i = 0; i < lineHeight; ++i)
  {
    std::cout << textgui_constants::thinLineChars[3]
              << "\033[1D\033[1B";
  }
}

void LineDrawService::drawHLine(unsigned lineLength, unsigned x, unsigned y) const
{
  std::cout << "\033[" << y << ";" << x << "H";
  for (unsigned i = 0; i < lineLength; ++i)
  {
    std::cout << textgui_constants::thinLineChars[12];
  }
}

void LineDrawService::drawVLine(unsigned lineHeight, unsigned x, unsigned y) const
{
  std::cout << "\033[" << y << ";" << x << "H";

  for (unsigned i = 0; i < lineHeight; ++i)
  {
    std::cout << textgui_constants::thinLineChars[3]
              << "\033[1D\033[1B";
  }
}

void LineDrawService::drawRect(unsigned w, unsigned h, unsigned x, unsigned y)
{

  std::cout << "\033[" << y << ";" << x << "H";
  drawVertex("TL");

  // Draw top line (Starting with cursor at leftX + 1, topY)
  drawHLine(w);

  // Render TRV (Starting with cursor at rightX, topY)
  drawVertex("TR");

  // Draw right line (Starting with cursor at rightX, topY + 1)
  std::cout << "\033[" << y + 1 << ";" << x + w+1 << "H";
  drawVLine(h-2);

  // Render BRV (Starting with cursor at rightX, botY)
  drawVertex("BR");

  // Draw left line (Starting with cursor at leftX, topY + 1)
  std::cout << "\033[" << y + 1 << ";" << x << "H";
  drawVLine(h-1);

  // Draw BLV and bottom line (Starting with cursor at leftX, botY)
  std::cout << "\033[" << y + h-1 << ";" << x << "H";
  drawVertex("BL");
  drawHLine(w);
}

void LineDrawService::drawVertex(FrameVertex *targetVertex) const
{
  unsigned vertexHash = hashIncomingEdges(targetVertex);
  std::cout << textgui_constants::thinLineChars[vertexHash];
}
void LineDrawService::drawVertex(std::string targetVertex) const
{
  if (targetVertex == "TL")
    std::cout << textgui_constants::thinLineChars[5];
  else if (targetVertex == "BL")
    std::cout << textgui_constants::thinLineChars[6];
  else if (targetVertex == "TR")
    std::cout << textgui_constants::thinLineChars[9];
  else if (targetVertex == "BR")
    std::cout << textgui_constants::thinLineChars[10];
}

//---------------------------
// Private Methods

unsigned LineDrawService::hashIncomingEdges(FrameVertex *targetVertex) const
{
  unsigned hashKey = 0;

  // b:lrtb
  if (targetVertex->getBottom())
  {
    hashKey += 1;
  }

  if (targetVertex->getTop())
  {
    hashKey += 2;
  }

  if (targetVertex->getRight())
  {
    hashKey += 4;
  }

  if (targetVertex->getLeft())
  {
    hashKey += 8;
  }

  return hashKey;
}
