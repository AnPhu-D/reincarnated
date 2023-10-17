#ifndef __CURSORSERVICE_H__
#define __CURSORSERVICE_H__

#include <iostream>

class CursorService {
 public:
  // Service Handle
  static CursorService* getService();

  // Delete the copy and assignment constructors
  CursorService(const CursorService&) = delete;
  CursorService& operator=(const CursorService&) = delete;

  // Service Methods
  void moveCursor(unsigned newX, unsigned newY);

 private:
  static CursorService* serviceHandle;

  CursorService() {
    serviceHandle = this;
  }
  ~CursorService() {}
};

#endif