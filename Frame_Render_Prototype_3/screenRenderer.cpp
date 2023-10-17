#include "screenRenderer.h"

// Render a frame with a background color and a frame color
void ScreenRenderer::renderFrameWithBackground(Frame* targetFrame, std::string backgroundColor, std::string frameColor) const {
  unsigned leftX = targetFrame->getX();
  unsigned topY = targetFrame->getY();

  unsigned fsizeX = targetFrame->getSX();
  unsigned fsizeY = targetFrame->getSY();

  fillAreaBackground(fsizeX, fsizeY, leftX, topY, backgroundColor);

  // Wrap drawFrame in highlightColor
  _HighlightService->startHighlightColor(backgroundColor);
  _TextColorService->startTextColor(frameColor);

  drawFrameContents(targetFrame);

  _TextColorService->endTextColor();
  _HighlightService->endHighlightColor();

  flushBuffer();
  _CursorService->moveCursor(101, 25);
}

// Render a frame without specifying a background color (use its own background color)
void ScreenRenderer::renderFrame(Frame* targetFrame) const {
  std::string backgroundColor = targetFrame->getBackgroundColor();
  std::string textColor = targetFrame->getTextColor();
  std::string borderColor = targetFrame->getBorderColor();
  renderFrameWithBackground(targetFrame, backgroundColor, borderColor);

  displayFrameText(targetFrame, backgroundColor, textColor);
  _CursorService->moveCursor(101, 25);
}

// Render a widget with highlight
void ScreenRenderer::highlightWidget(Widget* targetWidget) const {
  std::string backgroundColor = targetWidget->getHighlightColor();
  std::string textColor = targetWidget->getHighlightTextColor();
  std::string borderColor = targetWidget->getHighlightBorderColor();
  renderFrameWithBackground(targetWidget, backgroundColor, borderColor);
  _CursorService->moveCursor(101, 25);

  displayFrameText(targetWidget, backgroundColor, textColor);
  _CursorService->moveCursor(101, 25);
}

// Render a widget without highlight
void ScreenRenderer::unhighlightWidget(Widget* targetWidget) const {
  renderFrame(targetWidget);
  _CursorService->moveCursor(101, 25);
}

// Wipe the screen clean
void ScreenRenderer::clearScreen() const {
  std::cout << "\033[2J";
}

// Internals

// Helper to draw the contents of a frame
void ScreenRenderer::drawFrameContents(Frame* targetFrame) const {
  unsigned hLineCount = targetFrame->getSX() - 2;
  unsigned vLineCount = targetFrame->getSY() - 2;

  unsigned leftX = targetFrame->getX();
  unsigned rightX = leftX + targetFrame->getSX() - 1;

  unsigned topY = targetFrame->getY();
  unsigned botY = topY + targetFrame->getSY() - 1;

  // Draw Lines & Vertices
  if (targetFrame->borderShowing()) {
    // Render TLV (Starting with cursor at leftX, topY)
    _CursorService->moveCursor(leftX, topY);
    _LineDrawService->drawVertex(targetFrame->getTL());

    // Draw top line (Starting with cursor at leftX + 1, topY)
    _LineDrawService->drawHLine(hLineCount);

    // Render TRV (Starting with cursor at rightX, topY)
    _LineDrawService->drawVertex(targetFrame->getTR());

    // Draw right line (Starting with cursor at rightX, topY + 1)
    _CursorService->moveCursor(rightX, topY + 1);
    _LineDrawService->drawVLine(vLineCount);

    // Render BRV (Starting with cursor at rightX, botY)
    _LineDrawService->drawVertex(targetFrame->getBR());

    // Draw left line (Starting with cursor at leftX, topY + 1)
    _CursorService->moveCursor(leftX, topY + 1);
    _LineDrawService->drawVLine(vLineCount);

    // Draw BLV and bottom line (Starting with cursor at leftX, botY)
    _CursorService->moveCursor(leftX, botY);
    _LineDrawService->drawVertex(targetFrame->getBL());
    _LineDrawService->drawHLine(hLineCount);
  }
}

// Helper to fill an area with a background color
void ScreenRenderer::fillAreaBackground(unsigned width, unsigned height, unsigned tlx, unsigned tly, std::string fillColor) const {
  _HighlightService->startHighlightColor(fillColor);
  std::string blankString(width, ' ');

  for (unsigned i = 0; i < height; ++i) {
    // Move cursor to x=leftmost, y=top and down i
    _CursorService->moveCursor(tlx, tly + i);

    // Output the background-colored string
    cout << blankString;
  }
  _HighlightService->endHighlightColor();
}

// Helper to display the text of a frame
void ScreenRenderer::displayFrameText(Frame* targetFrame, std::string backgroundColor, std::string textColor) const {
  // Setup Cursor
  int borderOffset = 0;
  if (targetFrame->borderShowing()) {
    borderOffset = 1;
  }
  _CursorService->moveCursor(targetFrame->getX() + borderOffset, targetFrame->getY() + borderOffset);

  // Output Text
  _HighlightService->startHighlightColor(backgroundColor);
  _TextColorService->startTextColor(textColor);

  ScrollingWidget* castedScrollingWidget = dynamic_cast<ScrollingWidget*>(targetFrame);
  if (castedScrollingWidget != nullptr) {
    unsigned linesToDisplay = targetFrame->getSY() - 2;
    for (unsigned i = 0; i < linesToDisplay; ++i) {
      if (i > castedScrollingWidget->getTextLineCount() - 1) {
        break;
      }

      // Display Line Text
      _CursorService->moveCursor(targetFrame->getX() + borderOffset, targetFrame->getY() + borderOffset + i);
      cout << castedScrollingWidget->getTextLine(i);
    }
  } else if (targetFrame->getContainedText() != "") {
    std::cout << targetFrame->getContainedText();
  }
  _TextColorService->endTextColor();
  _HighlightService->endHighlightColor();
}