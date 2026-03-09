#include "telegram/TelegramBot.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

int main() {
    const char* token = std::getenv("TELEGRAM_BOT_TOKEN");
    if (!token) {
        std::cerr << "ERROR: TELEGRAM_BOT_TOKEN env var is not set\n";
        return 1;
    }

    try {
        telegram::TelegramBot bot(token);
        bot.run();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << '\n';
        return 2;
    }
}