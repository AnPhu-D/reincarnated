#ifndef __SCREENGUI_H__
#define __SCREENGUI_H__

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "frame.h"
#include "frameVertex.h"
#include "scrollingWidget.h"
#include "widget.h"

using namespace std;
// using std::vector as vector;

class ScreenGUI {
 public:
  // Constructor
  ScreenGUI(unsigned _sizeX, unsigned _sizeY)
      : vertexGrid(_sizeX, vector<FrameVertex*>(_sizeY)), charMem(_sizeX, vector<char>(_sizeY, 0)), sizeX(_sizeX), sizeY(_sizeY) {}
  ~ScreenGUI();

  // Mutators
  Frame* createFrame(unsigned fpx, unsigned fpy, unsigned fsx, unsigned fsy);
  Widget* createWidget(unsigned fpx, unsigned fpy, unsigned fsx, unsigned fsy);
  ScrollingWidget* createScrollingWidget(unsigned fpx, unsigned fpy, unsigned fsx, unsigned fsy);

  /// @brief Allocates and caches a new Framevertex.
  /// @param posX
  /// @param posY
  /// @return Pointer to the created FrameVertex.
  /// @throws std::logic_error if creating a new vertex where one already exists.
  /// @throws std::out_of_range
  /// @see ScreenGUI::checkPosition()
  FrameVertex* createFrameVertex(unsigned posX, unsigned posY, bool l, bool r, bool t, bool b);

  // Accessors
  const vector<Frame*>& getCreatedFrames() const;

 private:
  // Member Variables
  vector<Frame*> createdFrames;
  vector<FrameVertex*> createdFrameVertexes;

  vector<vector<FrameVertex*>> vertexGrid;
  vector<vector<char>> charMem;

  unsigned sizeX;
  unsigned sizeY;

  // Internal Helpers

  /// @brief Checks validity of position.
  /// @param posX
  /// @param posY
  /// @return bool isValid <-- true = valid, false = invalid
  bool checkPositionSafe(unsigned posX, unsigned posY);

  /// @brief Checks validity of position and throws an exception if invalid.
  /// @param posX
  /// @param posY
  /// @throws std::out_of_range when posX, posY, or both are out of range.
  void checkPositionUnsafe(unsigned posX, unsigned posY);

  /// @brief Gets the vertex at given coordinates if it exists.
  /// @param posX
  /// @param posY
  /// @return FrameVertex* that was found OR nullptr
  /// @throws std::out_of_range
  /// @see ScreenGUI::checkPosition()
  FrameVertex* getVertexAt(unsigned posX, unsigned posY);
};

#endif