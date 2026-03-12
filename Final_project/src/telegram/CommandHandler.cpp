#include "telegram/CommandHandler.h"

#include "core/ArbitrageBot.h"
#include "exchanges/Bybit.h"
#include "exchanges/OKX.h"

#include <exception>
#include <iomanip>
#include <sstream>
#include <vector>

namespace telegram {

namespace {

std::string buildMarketOverview() {
    Bybit bybitBtc("BTCUSDT", 99500.0, 99600.0);
    OKX okxBtc("BTCUSDT", 100100.0, 100200.0);

    Bybit bybitEth("ETHUSDT", 3450.0, 3460.0);
    OKX okxEth("ETHUSDT", 3490.0, 3500.0);

    std::ostringstream out;
    out << std::fixed << std::setprecision(2);

    out << "📊 Обзор рынка\n\n";

    out << "BTCUSDT\n";
    out << "• Bybit: bid = " << bybitBtc.getBid() << ", ask = " << bybitBtc.getAsk() << "\n";
    out << "• OKX:   bid = " << okxBtc.getBid() << ", ask = " << okxBtc.getAsk() << "\n\n";

    out << "ETHUSDT\n";
    out << "• Bybit: bid = " << bybitEth.getBid() << ", ask = " << bybitEth.getAsk() << "\n";
    out << "• OKX:   bid = " << okxEth.getBid() << ", ask = " << okxEth.getAsk();

    return out.str();}

    std::string buildDeals() {
    ArbitrageBot bot;
    bot.addExchange(std::make_unique<Bybit>("BTCUSDT", 99500.0, 99600.0));
    bot.addExchange(std::make_unique<OKX>("BTCUSDT", 100100.0, 100200.0));
    bot.addExchange(std::make_unique<Bybit>("ETHUSDT", 3450.0, 3460.0));
    bot.addExchange(std::make_unique<OKX>("ETHUSDT", 3490.0, 3500.0));

    std::ostringstream out;
    out << std::fixed << std::setprecision(2);

    try {
        auto opportunities = bot.findArbitrage();

        out << "💹 Выгодные операции\n\n";

        for (std::size_t i = 0; i < opportunities.size(); ++i) {
            const auto& buyOrder = opportunities[i].first;
            const auto& sellOrder = opportunities[i].second;

            double buyPrice = buyOrder.getPrice();
            double sellPrice = sellOrder.getPrice();
            double spread = sellPrice - buyPrice;
            double percent = (buyPrice == 0.0) ? 0.0 : (spread / buyPrice * 100.0);

            out << "Сделка #" << (i + 1) << "\n";
            out << "• Купить по: " << buyPrice << "\n";
            out << "• Продать по: " << sellPrice << "\n";
            out << "• Спред: " << spread << " (" << percent << "%)\n\n";
        }
    } catch (const std::exception& e) {
        out << "💹 Выгодные операции\n\n";
        out << "Сейчас подходящих возможностей нет: " << e.what();
    }

    return out.str();
}

std::string buildMoneyMessage() {
    const double buyPrice = 99600.0;
    const double sellPrice = 100100.0;
    const double spread = sellPrice - buyPrice;
    const double percent = spread / buyPrice * 100.0;

    std::ostringstream out;
    out << std::fixed << std::setprecision(2);

    out << "💰 Кнопка заработать деньги\n\n";
    out << "Лучшая идея в текущей симуляции:\n";
    out << "• Купить BTCUSDT на Bybit по " << buyPrice << "\n";
    out << "• Продать BTCUSDT на OKX по " << sellPrice << "\n\n";
    out << "Потенциальный спред: " << spread << " (" << percent << "%)";

    return out.str();
}

} // namespace

std::string CommandHandler::handleMessage(const std::string& text) const {
    if (text == "/start") {
        return "Выберите действие:";
    }

    if (text == "/market") {
        return buildMarketOverview();
    }

    if (text == "/deals") {
        return buildDeals();
    }

    if (text == "/money") {
        return buildMoneyMessage();
    }

    return "Напишите /start, чтобы открыть меню.\nИли используйте: /market, /deals, /money";
}

std::string CommandHandler::handleCallback(const std::string& data) const {
    if (data == "market") {
        return buildMarketOverview();
    }

    if (data == "deals") {
        return buildDeals();
    }

    if (data == "money") {
        return buildMoneyMessage();
    }

    return "Неизвестная кнопка.";
}

} // namespace telegram
