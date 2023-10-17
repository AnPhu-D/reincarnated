#ifndef __LINEDRAWSERVICE_H__
#define __LINEDRAWSERVICE_H__

#include <iostream>
#include <string>

#include "frameVertex.h"
#include "textgui_constants.h"


class LineDrawService
{
public:
  // Service Handle
  static LineDrawService *getService();

  // Delete the copy and assignment constructors
  LineDrawService(const LineDrawService &) = delete;
  LineDrawService &operator=(const LineDrawService &) = delete;

  // Service Methods
  void drawHLine(unsigned lineLength) const;
  void drawHLine(unsigned lineLength, unsigned x, unsigned y) const;
  void drawVLine(unsigned lineHeight) const;
  void drawVLine(unsigned lineHeight, unsigned x, unsigned y) const;

  void drawVertex(std::string) const;
  void drawVertex(FrameVertex *targetVertex) const;

  void drawRect(unsigned w, unsigned h, unsigned x, unsigned y);

private:
  static LineDrawService *serviceHandle;

  LineDrawService()
  {
    serviceHandle = this;
  }
  ~LineDrawService() {}

  unsigned hashIncomingEdges(FrameVertex *targetVertex) const;
};

#endif