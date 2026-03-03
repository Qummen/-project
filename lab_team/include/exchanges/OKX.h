#pragma once
#include "core/Exchange.h"
#include <string>
#include <utility>

class OKX : public Exchange {
private:
    std::string _pair;
    double bid;
    double ask;
public:
    OKX(std::string pair, double buyPrice, double sellPrice):
    _pair(std::move(pair)),bid(buyPrice), ask(sellPrice){}

    [[nodiscard]] double getBid() const override {
        return bid;
    }

    [[nodiscard]] double getAsk() const override {
        return ask;
    }

    [[nodiscard]] std::string nameStock() const override {
        return _pair;
    }

    [[nodiscard]] std::string nameExchange() const override {
        return "OKX";
    }
};