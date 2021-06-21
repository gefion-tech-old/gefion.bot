#include <tgbot/tgbot.h>

#include <cstring>
#include <iostream>

#include "headers/config.h"
#include "headers/messages.h"

using namespace std;
using namespace TgBot;

int main(int argc, char const* argv[]) {
  setlocale(LC_ALL, "ru");

  // проверяю минимальное кол-во аргументов
  if (argc < 3) {
    cout << "\x1b[31mError: \x1b[0m" << ERROR__TOKEN_UNDEFINED << endl;
    exit(1);
  }

  bool DEFAULT = false;

  // перебираю флаги и аргументы
  for (int arg = 1; arg < argc; arg++) {
    // если найден флаг токена
    if (strcmp(argv[arg], TOKEN_FLAG__SHORT) == 0 ||
        strcmp(argv[arg], TOKEN_FLAG) == 0) {
      // проверяю корректно ли указан аргумент флага
      if (argv[arg + 1][0] != '-') {
        TOKEN = argv[arg + 1];
      } else {
        cout << "\x1b[31mError: \x1b[0m" << ERROR__TOKEN_INCORRECTLY << endl;
        exit(1);
      }
      // если найден флаг дефолтного подключения
    } else if (strcmp(argv[arg], DEFAULT_FLAG__SHORT) == 0 ||
               strcmp(argv[arg], DEFAULT_FLAG) == 0) {
      DEFAULT = true;
    }
  }

  // инициализация бота
  Bot bot(TOKEN);

  // пробная обработка команд
  bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Hi!");
  });

  try {
    cout << "Bot " << bot.getApi().getMe()->username.c_str() << "is found"
         << endl;
    bot.getApi().deleteWebhook();

    TgLongPoll longPoll(bot);
    while (true) {
      cout << "Check for updates..." << endl;
      longPoll.start();
    }
  } catch (exception& e) {
    cout << "\x1b[31mError: \x1b[0m" << e.what() << endl;
  }

  return 0;
}
