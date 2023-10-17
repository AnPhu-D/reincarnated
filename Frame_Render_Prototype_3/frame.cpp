#include "frame.h"

// Clean up
Frame::~Frame() {}

// Check if the frame is visible
bool Frame::isVisible() const {
  return visible;
}

// Set the visibility of the frame
void Frame::setVisible(bool visiblityState) {
  visible = visiblityState;
}

// Get the text of the frame
std::string Frame::getContainedText() const {
  return containedText;
}

// Set the text of the frame
void Frame::setContainedText(std::string _containedText) {
  containedText = _containedText;
}

//---
// Get whether or not the frame has a border
bool Frame::borderShowing() const {
  return borderVisible;
}

// Make the frame show a border, ignore if the frame is too small
void Frame::showBorder() {
  if (sizeY < 3) {
    return;
  }
  if (sizeX < 2) {
    return;
  }
  borderVisible = true;
}

// Make the frame hide a border
void Frame::hideBorder() {
  borderVisible = false;
}

// Set the background color of the frame
void Frame::setBackgroundColor(std::string _bgColor) {
  bgColor = _bgColor;
}

// Set the text color of the frame
void Frame::setTextColor(std::string _textColor) {
  textColor = _textColor;
}

// Set the border color of the frame
void Frame::setBorderColor(std::string _borderColor) {
  borderColor = _borderColor;
}