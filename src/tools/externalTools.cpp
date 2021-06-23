#include "../headers/externalTools.h"

#include <iostream>
#include <string>

using namespace std;

void PrintError(char const e[]) {
  // code
  cout << "\x1b[31mError: \x1b[0m" << e << endl;
}

void ShowHelpInfo() {
  // code
  cout << "f" << endl;
}
