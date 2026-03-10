cmake_minimum_required(VERSION 3.20)
project(arbitrage_bot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

include(FetchContent)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(json)

add_executable(arbitrage-bot
        main.cpp
        src/telegram/TelegramBot.cpp
        src/telegram/CommandHandler.cpp
        src/core/Exchange.cpp
        src/exchanges/OKX.cpp
)

target_include_directories(arbitrage-bot PRIVATE
        include
)

target_link_libraries(arbitrage-bot PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)