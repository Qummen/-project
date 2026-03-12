#pragma once

#include "Exchange.h"
#include "Order.h"

#include <memory>
#include <optional>
#include <utility>
#include <vector>

class ArbitrageBot {
private:
    std::vector<std::unique_ptr<Exchange>> exchanges_;

public:
    void addExchange(std::unique_ptr<Exchange> ex);

    std::vector<std::pair<Order, Order>> findArbitrage();
    std::optional<std::pair<Order, Order>> findBestArbitrage() const;
};