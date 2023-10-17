#ifndef __SCREENRENDERER_H__
#define __SCREENRENDERER_H__

#include <iomanip>
#include <iostream>
#include <string>

#include "cursorService.h"
#include "highlightService.h"
#include "lineDrawService.h"
#include "services.h"

#include "frame.h"
#include "screenGui.h"
#include "textgui_constants.h"
#include "widget.h"

using Services::_CursorServiceHandle;
using Services::_HighlightServiceHandle;
using Services::_LineDrawServiceHandle;
using Services::_TextColorServiceHandle;

class ScreenRenderer {
 public:
  // Constructor a
  ScreenRenderer() {
  }

  // Public Methods
  void renderFrame(Frame* targetFrame) const;

  void highlightWidget(Widget* targetWidget) const;
  void unhighlightWidget(Widget* targetWidget) const;
  void renderFrameWithBackground(Frame* targetFrame, std::string backgroundColor, std::string frameColor) const;

  void clearScreen() const;

 private:
  // Service Declarations
  CursorService* _CursorService = _CursorServiceHandle;
  LineDrawService* _LineDrawService = _LineDrawServiceHandle;
  HighlightService* _HighlightService = _HighlightServiceHandle;
  TextColorService* _TextColorService = _TextColorServiceHandle;

  unsigned cursorX = 0;
  unsigned cursorY = 0;

  // Internal Helpers
  // Drawing Helpers
  void drawFrameContents(Frame* targetFrame) const;
  void fillAreaBackground(unsigned width, unsigned height, unsigned tlx, unsigned tly, std::string fillColor) const;
  void displayFrameText(Frame* targetFrame, std::string backgroundColor, std::string textColor) const;

  void flushBuffer() const { cout.flush(); }
};

#endif