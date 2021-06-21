#include <cstring>
#include <iostream>

#include "headers/config.h"

using namespace std;

int main(int argc, char const *argv[]) {
  setlocale(LC_ALL, "ru");

  // проверяю указан ли токен
  if (argc < 3) {
    cout << "\x1b[31mError: \x1b[0m"
         << "Токен не был указан в качестве параметра" << endl;
    exit(1);
  }

  // перебираю флаги и аргументы
  for (int arg = 1; arg < argc; arg++) {
    // если найден флаг токена
    if (strcmp(argv[arg], TOKEN_FLAG__SHORT) == 0 ||
        strcmp(argv[arg], TOKEN_FLAG) == 0) {
      // проверяю корректно ли указан аргумент флага
      if (argv[arg + 1][0] != '-') {
        TOKEN = argv[arg + 1];
      } else {
        cout << "\x1b[31mError: \x1b[0m"
             << "Токен указан неверно" << endl;
        exit(1);
      }
    }
  }

  return 0;
}
