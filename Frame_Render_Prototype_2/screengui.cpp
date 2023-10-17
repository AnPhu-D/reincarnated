#include "screengui.h"
#include "assert.h"

#include<iostream>

using std::cout;
using std::endl;

ScreenGUI::ScreenGUI(const unsigned sizeX, const unsigned sizeY)
    : _sizeX(sizeX), _sizeY(sizeY), occupancy(sizeX, vector<bool>(sizeY, false)) {
    }

//--------------------------------------------------------------

void ScreenGUI::AddFrame(const Frame& targetFrame) {
  // Insertion Validation
  assert(targetFrame.x() < _sizeX);
  assert(targetFrame.y() < _sizeY);

  assert(targetFrame.x() + targetFrame.sX() - 2 < _sizeX);
  assert(targetFrame.y() + targetFrame.sY() - 2 < _sizeY);

  frames.push_back(targetFrame);
  CacheFrameOccupancy(targetFrame);
}

void ScreenGUI::CacheFrameOccupancy(const Frame& targetFrame) {
  for (unsigned i = 0; i < targetFrame.sX(); ++i) {
    occupancy[targetFrame.x() + i][targetFrame.y()] = true;
    occupancy[targetFrame.x() + i][targetFrame.y() + targetFrame.sY() - 1] = true;
  }
  for (unsigned i = 0; i < targetFrame.sY(); ++i) {
    occupancy[targetFrame.x()][targetFrame.y()+i] = true;
    occupancy[targetFrame.x() + targetFrame.sX() - 1][targetFrame.y()+i] = true;
  }
}