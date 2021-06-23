#include <tgbot/tgbot.h>

#include <cstring>
#include <iostream>
#include <string>

#include "headers/config.h"
#include "headers/externalTools.h"
#include "headers/messages.h"
#include "headers/params.h"

using namespace std;
using namespace TgBot;

int main(int argc, char const* argv[]) {
  setlocale(LC_ALL, "ru");

  string TOKEN;

  // проверяю минимальное кол-во аргументов
  if (argc < 2) {
    PrintError(msg::ERROR__TOKEN_UNDEFINED);
    exit(1);
  }

  // bool DEFAULT = false;

  // перебираю флаги и аргументы
  for (int arg = 1; arg < argc; arg++) {
    // если найден флаг токена
    if (strcmp(argv[arg], params::TOKEN_FLAG__SHORT) == 0 ||
        strcmp(argv[arg], params::TOKEN_FLAG) == 0) {
      // проверяю указан ли параметр
      if (argc >= 3) {
        // проверяю корректно ли указан аргумент флага
        if (argv[arg + 1][0] != '-') {
          TOKEN = argv[arg + 1];
        } else {
          PrintError(msg::ERROR__TOKEN_INCORRECTLY);
          exit(1);
        }
      } else {
        PrintError(msg::ERROR__TOKEN_INCORRECTLY);
        exit(1);
      }

      // если присутствует флаг дефолтного подключения
    } else if (strcmp(argv[arg], params::DEFAULT_FLAG__SHORT) == 0 ||
               strcmp(argv[arg], params::DEFAULT_FLAG) == 0) {
      // DEFAULT = true;
    } else if (strcmp(argv[arg], params::HELP_FLAG__SHORT) == 0 ||
               strcmp(argv[arg], params::HELP_FLAG) == 0) {
      ShowHelpInfo();
      exit(1);
    }
  }

  // очищаю консоль
  system("clear");

  // инициализация бота
  Bot bot(TOKEN);

  //пробная обработка команд
  bot.getEvents().onCommand("start", [&bot](Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Hi!");
  });

  try {
    cout << "Bot "
         << "\x1b[33m" << bot.getApi().getMe()->username.c_str() << "\x1b[0m"
         << " is found." << endl
         << endl;
    bot.getApi().deleteWebhook();

    TgLongPoll longPoll(bot);
    while (true) {
      cout << "Check for updates..." << endl;
      longPoll.start();
    }
  } catch (exception& e) {
    PrintError(e.what());
  }

  return 0;
}
