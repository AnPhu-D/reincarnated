#include<iostream>
#include "frame.h"

using std::string;

Frame::Frame(unsigned posX, unsigned posY, unsigned sizeX, unsigned sizeY) {
  // Input Validation
  assert(sizeX > 1);
  assert(sizeY > 1);

  // Assignment
  _posX = posX;
  _posY = posY;
  _sizeX = sizeX;
  _sizeY = sizeY;

  _textContents = "";
}

Frame::Frame(const unsigned posX, const unsigned posY, const unsigned sizeX, const unsigned sizeY, const string& textContents)
    : Frame(posX, posY, sizeX, sizeY) {
  assert(textContents.length() <= (sizeX - 2));
  _textContents = textContents;
}