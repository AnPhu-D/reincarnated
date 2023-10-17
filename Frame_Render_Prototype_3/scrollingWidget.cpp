#include "scrollingWidget.h"

// Clean up the ScrollingWidget on destruction
ScrollingWidget::~ScrollingWidget() {
}

// Get the raw text of the ScrollingWidget
std::string ScrollingWidget::getRawText() const {
  return rawText;
}

// Set the raw text of the ScrollingWidget
void ScrollingWidget::setRawText(std::string _rawText) {
  rawText = _rawText;
  parseRawText();
}

//---
// Format the ScrollingWidget by ensuring that the text is not exceed the bounds of the ScrollingWidget
void ScrollingWidget::parseRawText() {
  rawTextAsLines.clear();
  std::string line;

  unsigned maxLineLength = getSX() - 2 - (2 * textXPadding);
  std::string xPaddingString(textXPadding, ' ');

  std::string::size_type pos = 0;
  std::string::size_type lastSpace = 0;

  std::string::size_type writeCount = 0;

  while (pos < rawText.length()) {
    if (rawText[pos] == ' ') {
      lastSpace = pos;
    }

    if (line.length() >= maxLineLength) {
      if (lastSpace != 0) {
        // Split the line at the last space
        std::string lineString = xPaddingString + line.substr(0, lastSpace - writeCount) + xPaddingString;
        rawTextAsLines.push_back(lineString);

        writeCount += lineString.size() - (2 * textXPadding);
        pos = lastSpace + 1;

        lastSpace = 0;
        line.clear();
      } else {
        // No space to split, so split the word
        rawTextAsLines.push_back(line);
        pos++;
        line.clear();
      }
    } else {
      line += rawText[pos++];
    }
  }

  // Add the last line
  if (!line.empty()) {
    std::string lineString = xPaddingString + line + xPaddingString;
    rawTextAsLines.push_back(lineString);
  }
}

// Get the number of lines of text in the ScrollingWidget
unsigned ScrollingWidget::getTextLineCount() const {
  return rawTextAsLines.size();
}

// Get a line of text from the ScrollingWidget
std::string ScrollingWidget::getTextLine(unsigned textLineIndex) const {
  if (textLineIndex > getTextLineCount())
    return "";
  return rawTextAsLines.at(textLineIndex);
}

// Get the text x padding of the ScrollingWidget
void ScrollingWidget::setTextXPadding(unsigned _textXPadding) {
  textXPadding = _textXPadding;
  parseRawText();
}