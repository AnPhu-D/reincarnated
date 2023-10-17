#include "keyPressedEvent.h"

#include <iostream>
#include <string>

// Constructor for a KeyPressedEvent
KeyPressedEvent::KeyPressedEvent(std::string _eventID)
    : Event(_eventID) {}

// Set what key to detect
void KeyPressedEvent::setParams(int _inputObject) {
  inputObject = _inputObject;
}

// Get the key to detect
int KeyPressedEvent::getInputObject() const {
  return inputObject;
}