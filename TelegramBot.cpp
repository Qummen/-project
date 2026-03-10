#include "telegram/TelegramBot.h"

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>

namespace telegram {

using json = nlohmann::json;

TelegramBot::TelegramBot(std::string token)
    : token_(std::move(token)),
      baseUrl_("https://api.telegram.org/bot" + token_) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

std::size_t TelegramBot::writeCallback(void* contents, std::size_t size, std::size_t nmemb, void* userp) {
    const std::size_t totalSize = size * nmemb;
    auto* output = static_cast<std::string*>(userp);
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string TelegramBot::httpGet(const std::string& url) const {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to init CURL");
    }

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &TelegramBot::writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    const CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        std::string error = curl_easy_strerror(result);
        curl_easy_cleanup(curl);
        throw std::runtime_error("GET request failed: " + error);
    }

    curl_easy_cleanup(curl);
    return response;
}

std::string TelegramBot::httpPost(const std::string& url, const std::string& jsonBody) const {
    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to init CURL");
    }

    std::string response;
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &TelegramBot::writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    const CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        std::string error = curl_easy_strerror(result);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        throw std::runtime_error("POST request failed: " + error);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return response;
}

void TelegramBot::sendMessage(std::int64_t chatId, const std::string& text) const {
    const std::string url = baseUrl_ + "/sendMessage";

    json body = {
        {"chat_id", chatId},
        {"text", text}
    };

    const std::string response = httpPost(url, body.dump());
    const json parsed = json::parse(response);

    if (!parsed.contains("ok") || !parsed["ok"].get<bool>()) {
        throw std::runtime_error("Telegram sendMessage failed: " + response);
    }
}

void TelegramBot::pollUpdates() {
    std::string url = baseUrl_ + "/getUpdates?timeout=25";
    if (lastUpdateId_ > 0) {
        url += "&offset=" + std::to_string(lastUpdateId_);
    }

    const std::string response = httpGet(url);
    const json parsed = json::parse(response);

    if (!parsed.contains("ok") || !parsed["ok"].get<bool>()) {
        throw std::runtime_error("Telegram getUpdates failed: " + response);
    }

    for (const auto& update : parsed["result"]) {
        const std::int64_t updateId = update["update_id"].get<std::int64_t>();
        lastUpdateId_ = updateId + 1;

        if (!update.contains("message")) {
            continue;
        }

        const auto& message = update["message"];

        if (!message.contains("chat") || !message["chat"].contains("id")) {
            continue;
        }

        if (!message.contains("text")) {
            continue;
        }

        const std::int64_t chatId = message["chat"]["id"].get<std::int64_t>();
        const std::string text = message["text"].get<std::string>();

        const std::string answer = handler_.handleMessage(text);
        sendMessage(chatId, answer);
    }
}

void TelegramBot::run() {
    std::cout << "Bot started. Long polling...\n";

    while (true) {
        try {
            pollUpdates();
        } catch (const std::exception& e) {
            std::cerr << "Polling error: " << e.what() << '\n';
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

}