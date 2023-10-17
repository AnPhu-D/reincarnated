#include "widget.h"

// Clean up the widget on destruction
Widget::~Widget() {
}

// Get the highlight color of the widget
std::string Widget::getHighlightColor() const {
  return highlightColor;
}

// Set the highlight color of the widget
void Widget::setHighlightColor(std::string _highlightColor) {
  highlightColor = _highlightColor;
}

// Get the text color of the widget
std::string Widget::getHighlightTextColor() const {
  return highlightTextColor;
}

// Set the text color of the widget
void Widget::setHighlightTextColor(std::string _highlightTextColor) {
  highlightTextColor = _highlightTextColor;
}

// Get the border color of the widget
std::string Widget::getHighlightBorderColor() const {
  return highlightBorderColor;
}

// Set the border color of the widget
void Widget::setHighlightBorderColor(std::string _highlightBorderColor) {
  highlightBorderColor = _highlightBorderColor;
}

// Attach a function to the widget for it to call when it is pressed
void Widget::bindFunction(std::function<void()> functionToBind) {
  onButtonPress = functionToBind;
}

// Attach a function to the widget for it to check if it can be pressed
void Widget::bindCheck(std::function<bool()> checkToBind) {
  canPressButton = checkToBind;
}