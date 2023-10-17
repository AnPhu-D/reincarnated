#ifndef __USERINPUTSERVICE_H__
#define __USERINPUTSERVICE_H__

#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "event.h"
#include "keyPressedEvent.h"

class UserInputService {
 public:
  // Service Handle
  static UserInputService* getService();
  static void deleteService();

  // Delete the copy and assignment constructors
  UserInputService(const UserInputService&) = delete;
  UserInputService& operator=(const UserInputService&) = delete;

  // Service Methods
  void launch();
  KeyPressedEvent* getKeyPressedEvent();

 private:
  static UserInputService* serviceHandle;
  KeyPressedEvent* keyPressedEventHandle;

  UserInputService() {
    serviceHandle = this;

    std::string keyPressedEventID = "keyPressedEvent";
    keyPressedEventHandle = new KeyPressedEvent(keyPressedEventID);
  }
  ~UserInputService() {
    delete keyPressedEventHandle;
  }

  // Internal Helpers & Members
  std::vector<int> internalInputBuffer;

  void configTerminal() const;
  void testParseInput(int input);
};

#endif