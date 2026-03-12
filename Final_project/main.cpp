#include "core/ArbitrageBot.h"
#include "exchanges/Bybit.h"
#include "exchanges/OKX.h"
#include "telegram/TelegramBot.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    try {
        std::cout << "=== Arbitrage bot ===\n";

        ArbitrageBot bot;
        bot.addExchange(std::make_unique<Bybit>("BTC/USDT", 99500.0, 99600.0));
        bot.addExchange(std::make_unique<OKX>("BTC/USDT", 100100.0, 100200.0));
        bot.addExchange(std::make_unique<Bybit>("ETH/USDT", 3450.0, 3460.0));
        bot.addExchange(std::make_unique<OKX>("ETH/USDT", 3490.0, 3500.0));
        try { auto opportunities = bot.findArbitrage();
            std::cout << "Found opportunities: " << opportunities.size() << "\n\n";
            for (std::size_t i = 0; i < opportunities.size(); ++i) {
                const auto& buyOrder  = opportunities[i].first;
                const auto& sellOrder = opportunities[i].second;
                std::cout << "Opportunity " << i + 1 << '\n';
                std::cout << "Buy price:  " << buyOrder.getPrice() << '\n';
                std::cout << "Sell price: " << sellOrder.getPrice() << "\n\n";
            }
        } catch (const std::exception& e) { std::cout << "Startup arbitrage scan skipping: " << e.what() << "\n\n"; }
        const char* token = std::getenv("TELEGRAM_BOT_TOKEN");
        if (token != nullptr){
            std::cout << "=== Telegram bot startuet ===\n";
            telegram::TelegramBot tgBot(token);
            tgBot.run();
        } else {
            std::cout << "TELEGRAM_BOT_TOKEN is not set, Telegram bot skipping.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "!!!Fatal error!!!: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

