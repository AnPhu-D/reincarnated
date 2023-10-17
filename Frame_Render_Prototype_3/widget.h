#ifndef WIDGET_H
#define WIDGET_H

#include <functional>
#include <string>

#include "frame.h"

struct Widget : public Frame {
 public:
  Widget(unsigned _x, unsigned _y, unsigned _sizeX, unsigned _sizeY, FrameVertex* tl, FrameVertex* tr, FrameVertex* bl, FrameVertex* br)
      : Frame(_x, _y, _sizeX, _sizeY, tl, tr, bl, br), highlightColor("White"), highlightTextColor("Default"), highlightBorderColor("Default") {}
  ~Widget() override;

  std::string getHighlightColor() const;
  void setHighlightColor(std::string _highlightColor);

  std::string getHighlightTextColor() const;
  void setHighlightTextColor(std::string _highlightTextColor);

  std::string getHighlightBorderColor() const;
  void setHighlightBorderColor(std::string _highlightBorderColor);

  void bindFunction(std::function<void()> functionToBind);
  std::function<void()> onButtonPress;

  void bindCheck(std::function<bool()> checkToBind);
  std::function<bool()> canPressButton = []() -> bool { return true; };

 private:
  std::string highlightColor;
  std::string highlightTextColor;
  std::string highlightBorderColor;
};

#endif