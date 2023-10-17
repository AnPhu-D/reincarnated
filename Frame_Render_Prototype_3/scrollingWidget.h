#ifndef __SCROLLINGWIDGET_H__
#define __SCROLLINGWIDGET_H__

#include <iostream>
#include <vector>

#include "widget.h"

class ScrollingWidget : public Widget {
 public:
  ScrollingWidget(unsigned _x, unsigned _y, unsigned _sizeX, unsigned _sizeY, FrameVertex* tl, FrameVertex* tr, FrameVertex* bl, FrameVertex* br)
      : Widget(_x, _y, _sizeX, _sizeY, tl, tr, bl, br), rawText("") {}
  ~ScrollingWidget() override;

  std::string getRawText() const;
  void setRawText(std::string _rawText);

  unsigned getTextLineCount() const;
  std::string getTextLine(unsigned textLineIndex) const;

  unsigned getTextXPadding() const { return textXPadding; }
  void setTextXPadding(unsigned _textXPadding);

 private:
  std::string rawText;
  vector<std::string> rawTextAsLines;
  unsigned textXPadding = 0;

  void parseRawText();
};

#endif