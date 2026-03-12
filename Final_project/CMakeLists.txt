cmake_minimum_required(VERSION 3.16)
project(lab_team)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

find_package(CURL REQUIRED)

find_package(nlohmann_json QUIET)
if(NOT nlohmann_json_FOUND)
    FetchContent_Declare(
            nlohmann_json
            URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()

add_executable(lab_team
        main.cpp
        include/core/Exchange.h
        src/core/Exchange.cpp
        include/exchanges/OKX.h
        src/exchanges/OKX.cpp
        include/core/ArbitrageBot.h
        src/core/ArbitrageBot.cpp
        include/exchanges/Bybit.h
        src/exchanges/Bybit.cpp
        include/core/order.h
        src/core/order.cpp
        include/market/market.h
        src/market/market.cpp
        include/telegram/CommandHandler.h
        include/telegram/TelegramBot.h
        src/telegram/CommandHandler.cpp
        src/telegram/TelegramBot.cpp
        src/core/ArbitrageBot.cpp
        src/core/ArbitrageBot.cpp
        src/core/ArbitrageBot.cpp
)

target_include_directories(lab_team PRIVATE include)

target_link_libraries(lab_team PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)
