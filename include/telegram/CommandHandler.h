#pragma once

#include <string>

namespace telegram {

    class CommandHandler {
    public:
        [[nodiscard]] std::string handleMessage(const std::string& text) const;
    };

}