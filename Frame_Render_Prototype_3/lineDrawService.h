#ifndef __LINEDRAWSERVICE_H__
#define __LINEDRAWSERVICE_H__

#include <iostream>

#include "frameVertex.h"
#include "textgui_constants.h"

class LineDrawService {
 public:
  // Service Handle
  static LineDrawService* getService();
  static void deleteService();

  // Delete the copy and assignment constructors
  LineDrawService(const LineDrawService&) = delete;
  LineDrawService& operator=(const LineDrawService&) = delete;

  // Service Methods
  void drawHLine(unsigned lineLength) const;
  void drawVLine(unsigned lineHeight) const;

  void drawVertex(FrameVertex* targetVertex) const;

 private:
  static LineDrawService* serviceHandle;

  LineDrawService() {
    serviceHandle = this;
  }
  ~LineDrawService() {}

  unsigned hashIncomingEdges(FrameVertex* targetVertex) const;
};

#endif