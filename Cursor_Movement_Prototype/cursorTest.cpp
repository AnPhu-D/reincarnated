#include <termios.h>
#include <unistd.h>

#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
 
using namespace std;

int main() {
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  //--------------------------------------

  ifstream menuText("menuPrototype.txt");
  cout << menuText.rdbuf();

  cout << "\033[7A";

  int user_input = 0;
  while (1) {
    user_input = 0;

    user_input = getchar();

    if (user_input == 65) {
      // Up
      cout << "\033[1A";
    } else if (user_input == 66) {
      // Down
      cout << "\033[1B";
    } else if (user_input == 68) {
      // Left
      cout << "\033[1D";
    } else if (user_input == 67) {
      // Right
      cout << "\033[1C";
    }
  }
}