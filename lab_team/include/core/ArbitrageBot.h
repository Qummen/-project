#pragma once
#include <vector>
#include <utility>
#include "Exchange.h"
#include "order.h"

class ArbitrageBot {
private:
    std::vector<const Exchange*> exchanges_;
public:
    void addExchange (const Exchange* exchange);

    [[nodiscard]] std::vector <std::pair<Order, Order>> findArbitrage();
};
