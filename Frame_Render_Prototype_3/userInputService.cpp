#include "userInputService.h"

#include <iostream>

#include "cursorService.h"

UserInputService* UserInputService::serviceHandle = nullptr;

// Constructor for a UserInputService
UserInputService* UserInputService::getService() {
  if (serviceHandle == nullptr) {
    serviceHandle = new UserInputService;
  }
  return serviceHandle;
}

// Delete the UserInputService
void UserInputService::deleteService() {
  delete serviceHandle;
}

// Launch the UserInputService
void UserInputService::launch() {
  configTerminal();

  int user_input = 0;
  while (1) {
    user_input = 0;
    user_input = getchar();

    CursorService::getService()->moveCursor(101, 25);
    std::cout << "   " << user_input << "   ";

    keyPressedEventHandle->setParams(user_input);
    keyPressedEventHandle->fire();
  }
}

// Get the KeyPressedEvent
KeyPressedEvent* UserInputService::getKeyPressedEvent() {
  return keyPressedEventHandle;
}

//------------------------
// Configure the terminal for getting user input
void UserInputService::configTerminal() const {
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void UserInputService::testParseInput(int input) {
  internalInputBuffer.push_back(input);

  // The only time buffer size is greater than 1 is when
  // the escape character is heard previously or there is
  // a sequence being written.
  if (internalInputBuffer.size() == 1) {
    if (input != 27) {
      std::cout << "Single Char: " << static_cast<char>(input) << std::endl;
      internalInputBuffer.clear();
    }
    return;
  }

  // TODO: Work on this

  // Clear the buffer if we do not recognize the sequence
  internalInputBuffer.clear();
}