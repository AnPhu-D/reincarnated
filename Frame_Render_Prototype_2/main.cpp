

#include<iostream>

#include "frame.h"
#include "screengui.h"

int main() {
  Frame testFrame(0,0,5,4);
  ScreenGUI testGUI(80,25);

  testGUI.AddFrame(testFrame);
}