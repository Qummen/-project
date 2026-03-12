#include "telegram/CommandHandler.h"

namespace telegram {

std::string CommandHandler::handleMessage(const std::string& text) const {
    if (text == "/start") {
        return "Выберите действие:";
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

std::string CommandHandler::handleCallback(const std::string& data) const {
    if (data == "market") {
        return "Обзор рынка пока в разработке.";
    }

    if (data == "deals") {
        return "Выгодные операции пока в разработке.";
    }

    if (data == "money") {
        return "Функция заработка пока в разработке.";
    }

    return "Неизвестная кнопка.";
}

} // namespace telegram
