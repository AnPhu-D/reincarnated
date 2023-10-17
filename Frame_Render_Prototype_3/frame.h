#ifndef __FRAME_H__
#define __FRAME_H__

#include <string>

#include "frameVertex.h"

using namespace std;

struct Frame {
 public:
  // Note that lifetime of vertices are linked to the ScreenGUI, not the Frame.
  Frame(unsigned _x, unsigned _y, unsigned _sizeX, unsigned _sizeY, FrameVertex* tl, FrameVertex* tr, FrameVertex* bl, FrameVertex* br)
      : x(_x), y(_y), sizeX(_sizeX), sizeY(_sizeY), topLeft(tl), topRight(tr), bottomLeft(bl), bottomRight(br), bgColor("none"), textColor("Default"), borderColor("Default"), containedText("") {
    if (sizeY < 3 || sizeX < 2) {
      hideBorder();
    }
  }
  virtual ~Frame();

  unsigned getX() const { return x; }
  unsigned getY() const { return y; }
  unsigned getSX() const { return sizeX; }
  unsigned getSY() const { return sizeY; }

  FrameVertex* getTL() const { return topLeft; }
  FrameVertex* getTR() const { return topRight; }
  FrameVertex* getBL() const { return bottomLeft; }
  FrameVertex* getBR() const { return bottomRight; }

  bool isVisible() const;
  void setVisible(bool visibilityState);

  bool borderShowing() const;
  void showBorder();
  void hideBorder();

  std::string getBackgroundColor() const { return bgColor; }
  void setBackgroundColor(std::string _bgColor);

  std::string getTextColor() const { return textColor; }
  void setTextColor(std::string _textColor);

  std::string getBorderColor() const { return borderColor; }
  void setBorderColor(std::string _borderColor);

  virtual void test() {}

  std::string getContainedText() const;
  void setContainedText(std::string _containedText);

 private:
  unsigned x;
  unsigned y;
  unsigned sizeX;
  unsigned sizeY;

  bool visible = true;

  bool borderVisible = true;

  std::string textColor;
  std::string bgColor;
  std::string borderColor;

  FrameVertex* topLeft;
  FrameVertex* topRight;
  FrameVertex* bottomLeft;
  FrameVertex* bottomRight;

  std::string containedText;
};

#endif