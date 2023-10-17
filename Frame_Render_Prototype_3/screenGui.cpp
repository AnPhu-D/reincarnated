#include "screenGui.h"

// Clean up the ScreenGUI on destruction
ScreenGUI::~ScreenGUI() {
  for (unsigned i = 0; i < createdFrameVertexes.size(); ++i) {
    delete createdFrameVertexes.at(i);
  }

  for (unsigned i = 0; i < createdFrames.size(); ++i) {
    delete createdFrames.at(i);
  }
}

// Public Mutators
Frame* ScreenGUI::createFrame(unsigned fpx, unsigned fpy, unsigned fsx, unsigned fsy) {
  // Validate parameters passed.
  bool canShowBorder = true;
  if (fsy < 3 && fsx >= 2) {
    canShowBorder = false;
    // throw std::invalid_argument("Invalid Frame Size Y argument (fsy < 3)");
  } else if (fsx < 2 && fsy >= 3) {
    canShowBorder = false;
    // throw std::invalid_argument("Invalid Frame Size X argument (fsx < 2)");
  } else if (fsx < 2 && fsy < 3) {
    canShowBorder = false;
    // throw std::invalid_argument("Invalid Frame Size X and Y argument (fsy < 2, fsy < 3)");
  }

  // Determine existing vertices
  unsigned tlX = fpx, tlY = fpy;
  unsigned trX = fpx + fsx - 1, trY = fpy;
  unsigned blX = fpx, blY = fpy + fsy - 1;
  unsigned brX = fpx + fsx - 1, brY = fpy + fsy - 1;

  FrameVertex* tl = getVertexAt(tlX, tlY);
  FrameVertex* tr = getVertexAt(trX, trY);
  FrameVertex* bl = getVertexAt(blX, blY);
  FrameVertex* br = getVertexAt(brX, brY);

  if (tl == nullptr) {
    tl = createFrameVertex(tlX, tlY, false, true, false, true);
  } else {
    tl->setRight(true);
    tl->setBottom(true);
  }
  if (tr == nullptr) {
    tr = createFrameVertex(trX, trY, true, false, false, true);
  } else {
    tr->setLeft(true);
    tr->setBottom(true);
  }
  if (bl == nullptr) {
    bl = createFrameVertex(blX, blY, false, true, true, false);
  } else {
    bl->setRight(true);
    bl->setTop(true);
  }
  if (br == nullptr) {
    br = createFrameVertex(brX, brY, true, false, true, false);
  } else {
    bl->setLeft(true);
    bl->setTop(true);
  }

  Frame* newFrame = new Frame(fpx, fpy, fsx, fsy, tl, tr, bl, br);
  if (!canShowBorder) {
    newFrame->hideBorder();
  }
  createdFrames.push_back(newFrame);

  return newFrame;
}

// Create a widget
Widget* ScreenGUI::createWidget(unsigned fpx, unsigned fpy, unsigned fsx, unsigned fsy) {
  // Validate parameters passed.
  bool canShowBorder = true;
  if (fsy < 3 && fsx >= 2) {
    canShowBorder = false;
    // throw std::invalid_argument("Invalid Frame Size Y argument (fsy < 3)");
  } else if (fsx < 2 && fsy >= 3) {
    canShowBorder = false;
    // throw std::invalid_argument("Invalid Frame Size X argument (fsx < 2)");
  } else if (fsx < 2 && fsy < 3) {
    canShowBorder = false;
    // throw std::invalid_argument("Invalid Frame Size X and Y argument (fsy < 2, fsy < 3)");
  }

  // Determine existing vertices
  unsigned tlX = fpx, tlY = fpy;
  unsigned trX = fpx + fsx - 1, trY = fpy;
  unsigned blX = fpx, blY = fpy + fsy - 1;
  unsigned brX = fpx + fsx - 1, brY = fpy + fsy - 1;

  FrameVertex* tl = getVertexAt(tlX, tlY);
  FrameVertex* tr = getVertexAt(trX, trY);
  FrameVertex* bl = getVertexAt(blX, blY);
  FrameVertex* br = getVertexAt(brX, brY);

  if (tl == nullptr) {
    tl = createFrameVertex(tlX, tlY, false, true, false, true);
  } else {
    tl->setRight(true);
    tl->setBottom(true);
  }
  if (tr == nullptr) {
    tr = createFrameVertex(trX, trY, true, false, false, true);
  } else {
    tr->setLeft(true);
    tr->setBottom(true);
  }
  if (bl == nullptr) {
    bl = createFrameVertex(blX, blY, false, true, true, false);
  } else {
    bl->setRight(true);
    bl->setTop(true);
  }
  if (br == nullptr) {
    br = createFrameVertex(brX, brY, true, false, true, false);
  } else {
    bl->setLeft(true);
    bl->setTop(true);
  }

  Widget* newWidget = new Widget(fpx, fpy, fsx, fsy, tl, tr, bl, br);
  if (!canShowBorder) {
    newWidget->hideBorder();
  }
  createdFrames.push_back(newWidget);

  return newWidget;
}

// Create a scrolling widget
ScrollingWidget* ScreenGUI::createScrollingWidget(unsigned fpx, unsigned fpy, unsigned fsx, unsigned fsy) {
  // Validate parameters passed.
  bool canShowBorder = true;
  if (fsy < 3 && fsx >= 2) {
    canShowBorder = false;
    // throw std::invalid_argument("Invalid Frame Size Y argument (fsy < 3)");
  } else if (fsx < 2 && fsy >= 3) {
    canShowBorder = false;
    // throw std::invalid_argument("Invalid Frame Size X argument (fsx < 2)");
  } else if (fsx < 2 && fsy < 3) {
    canShowBorder = false;
    // throw std::invalid_argument("Invalid Frame Size X and Y argument (fsy < 2, fsy < 3)");
  }

  // Determine existing vertices
  unsigned tlX = fpx, tlY = fpy;
  unsigned trX = fpx + fsx - 1, trY = fpy;
  unsigned blX = fpx, blY = fpy + fsy - 1;
  unsigned brX = fpx + fsx - 1, brY = fpy + fsy - 1;

  FrameVertex* tl = getVertexAt(tlX, tlY);
  FrameVertex* tr = getVertexAt(trX, trY);
  FrameVertex* bl = getVertexAt(blX, blY);
  FrameVertex* br = getVertexAt(brX, brY);

  if (tl == nullptr) {
    tl = createFrameVertex(tlX, tlY, false, true, false, true);
  } else {
    tl->setRight(true);
    tl->setBottom(true);
  }
  if (tr == nullptr) {
    tr = createFrameVertex(trX, trY, true, false, false, true);
  } else {
    tr->setLeft(true);
    tr->setBottom(true);
  }
  if (bl == nullptr) {
    bl = createFrameVertex(blX, blY, false, true, true, false);
  } else {
    bl->setRight(true);
    bl->setTop(true);
  }
  if (br == nullptr) {
    br = createFrameVertex(brX, brY, true, false, true, false);
  } else {
    bl->setLeft(true);
    bl->setTop(true);
  }

  ScrollingWidget* newScrollingWidget = new ScrollingWidget(fpx, fpy, fsx, fsy, tl, tr, bl, br);
  createdFrames.push_back(newScrollingWidget);
  if (!canShowBorder) {
    newScrollingWidget->hideBorder();
  }
  return newScrollingWidget;
}

// Create a frame vertex
FrameVertex* ScreenGUI::createFrameVertex(unsigned posX, unsigned posY, bool l, bool r, bool t, bool b) {
  // Validate parameters passed.
  if (getVertexAt(posX, posY) != nullptr) {
    throw std::invalid_argument("Tried to create a new vertex where one already exists.");
  }

  FrameVertex* newFrameVertex = new FrameVertex(l, r, t, b);
  createdFrameVertexes.push_back(newFrameVertex);
  vertexGrid.at(posX).at(posY) = newFrameVertex;

  return newFrameVertex;
}

//-------------------------------
// Internal Helpers
bool ScreenGUI::checkPositionSafe(unsigned posX, unsigned posY) {
  if (posX >= sizeX && posY < sizeY) {
    return false;
  } else if (posY >= sizeY && posX < sizeX) {
    return false;
  } else if (posX >= sizeX && posY >= sizeY) {
    return false;
  }
  return true;
}

// Check if the position is in bounds, throw an exception if not
void ScreenGUI::checkPositionUnsafe(unsigned posX, unsigned posY) {
  if (posX >= sizeX && posY < sizeY) {
    throw std::out_of_range("posX index out of bounds.");
  } else if (posY >= sizeY && posX < sizeX) {
    throw std::out_of_range("posY index out of bounds.");
  } else if (posX >= sizeX && posY >= sizeY) {
    throw std::out_of_range("posX and posY indices out of bounds.");
  }
}

// Get a vertex at a position
FrameVertex* ScreenGUI::getVertexAt(unsigned posX, unsigned posY) {
  // Verify position is in bounds
  checkPositionUnsafe(posX, posY);
  return vertexGrid.at(posX).at(posY);
}

// Accessors
const vector<Frame*>& ScreenGUI::getCreatedFrames() const {
  return createdFrames;
}