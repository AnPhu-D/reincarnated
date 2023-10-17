#ifndef __SCREENGUI_H__
#define __SCREENGUI_H__

#include <vector>
#include "frame.h"

using std::vector;

struct ScreenGUI {
 public:
  // Constructor
  ScreenGUI(const unsigned, const unsigned);

  // Frame Methods
  void AddFrame(const Frame&);

 private:
  // ScreenGUI Data
  unsigned _sizeX;
  unsigned _sizeY;

  // Frame Container
  vector<Frame> frames;
  vector<vector<bool>> occupancy;

  // Occupancy Writer
  void CacheFrameOccupancy(const Frame&);

};

#endif