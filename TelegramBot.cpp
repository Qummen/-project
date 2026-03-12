#include "telegram/TelegramBot.h"

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include <stdexcept>
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
        const std::string error = curl_easy_strerror(result);
        curl_easy_cleanup(curl);
        throw std::runtime_error("GET request failed: " + error);
    }

    curl_easy_cleanup(curl);
    return response;
}

void TelegramBot::sendMessage(std::int64_t, const std::string&) const {
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
    }
}

void TelegramBot::run() {
    while (true) {
        pollUpdates();
    }
}

} // namespace telegram
