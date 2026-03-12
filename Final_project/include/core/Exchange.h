#pragma once

#include <string>

class Exchange {
public:
    virtual ~Exchange() = 0;
    [[nodiscard]] virtual double getBid() const = 0;
    [[nodiscard]] virtual double getAsk() const = 0;
    [[nodiscard]] virtual std::string nameStock() const = 0;
    [[nodiscard]] virtual std::string nameExchange() const = 0;
};
