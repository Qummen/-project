#include "telegram/CommandHandler.h"

namespace telegram {

    std::string CommandHandler::handleMessage(const std::string& text) const {
        if (text == "/start") {
            return "ну шо ты хузлик";
        }

        if (text == "/help") {
            return "Доступные команды:\n/start\n/help";
        }

        return "Эхо: " + text;
    }

}