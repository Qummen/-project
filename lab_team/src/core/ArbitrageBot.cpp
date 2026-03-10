#include "core/ArbitrageBot.h"
#include <stdexcept>
#include <algorithm>

void ArbitrageBot::addExchange(std::unique_ptr<Exchange> ex){
    exchanges_.push_back(std::move(ex));
}

std::vector <std::pair<Order, Order>>  ArbitrageBot::findArbitrage() {
    std::vector<std::pair<Order, Order>> goodPairs;
    while (!exchanges_.empty()) {
        if (exchanges_.size() < 2) {
            throw std::runtime_error("We need minimum 2 exchanges");
        }

        const Exchange* buyExchange = nullptr;
        const Exchange* sellExchange = nullptr;

        double bestBuy  = 1000001;
        double bestSell = - 1000001;

        for for (const auto& ex : exchanges_) {
            if (ex->getAsk() < bestBuy) {
                bestBuy = ex->getAsk();
                buyExchange = ex.get();
            }
            if (ex->getBid() < bestSell) {
                bestSell = ex->getBid();
                sellExchange = ex.get();
            }
        }

        if (bestBuy >= bestSell * 0.99) {
            throw std::runtime_error("No opportunity");
        }

        Order buyOrder(buyExchange->nameStock(), buyExchange->nameExchange(), bestBuy, OrderType::BUY);
        Order sellOrder(sellExchange->nameStock(), sellExchange->nameExchange(), bestSell, OrderType::SELL);
        goodPairs.emplace_back(buyOrder, sellOrder);

        exchanges_.erase(
        std::remove_if(
        exchanges_.begin(),
        exchanges_.end(),
        [buyExchange](const std::unique_ptr<Exchange>& ex) {
            return ex.get() == buyExchange;
        }
    ),
    exchanges_.end()
);
    }

    return goodPairs;

}


