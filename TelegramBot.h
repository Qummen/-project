#pragma once

#include "telegram/CommandHandler.h"

#include <cstdint>
#include <string>

namespace telegram {

    class TelegramBot {
    public:
        explicit TelegramBot(std::string token);

        void run();

    private:
        std::string token_;
        std::string baseUrl_;
        std::int64_t lastUpdateId_ = 0;
        CommandHandler handler_;

        static std::size_t writeCallback(void* contents, std::size_t size, std::size_t nmemb, void* userp);

        std::string httpGet(const std::string& url) const;
        std::string httpPost(const std::string& url, const std::string& jsonBody) const;

        void pollUpdates();
        void sendMessage(std::int64_t chatId, const std::string& text) const;
    };

}