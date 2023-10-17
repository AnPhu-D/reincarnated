#ifndef __FRAME_H__
#define __FRAME_H__

#include <assert.h>
#include <string>

using std::string;

struct Frame {
 public:
  Frame(const unsigned, const unsigned, const unsigned, const unsigned);
  Frame(const unsigned, const unsigned, const unsigned, const unsigned, const string&);

  string getText() { return _textContents; }
  unsigned x() const { return _posX; }
  unsigned y() const { return _posY; }

  unsigned sX() const { return _sizeX; }
  unsigned sY() const { return _sizeY; }

 private:
  unsigned _posX;
  unsigned _posY;

  unsigned _sizeX;
  unsigned _sizeY;

  string _textContents;
};

#endif