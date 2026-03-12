#include "telegram/CommandHandler.h"

namespace telegram {

std::string CommandHandler::handleMessage(const std::string& text) const {
    if (text == "/start") {
        return "Бот запущен. Используйте команды /market, /deals, /money";
    }

    if (text == "/market") {
        return "Обзор рынка пока в разработке.";
    }

    if (text == "/deals") {
        return "Выгодные операции пока в разработке.";
    }

    if (text == "/money") {
        return "Функция заработка пока в разработке.";
    }

    return "Неизвестная команда.";
}

} // namespace telegram
