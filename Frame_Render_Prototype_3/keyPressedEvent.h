#ifndef __KEYPRESSEDEVENT_H__
#define __KEYPRESSEDEVENT_H__

#include "event.h"

class KeyPressedEvent : public Event {
 public:
  // Constructor
  KeyPressedEvent(std::string _eventID);

  // Public Methods
  void setParams(int _inputObject);
  // void fire() const override;

  int getInputObject() const;

 private:
  int inputObject;
};

#endif