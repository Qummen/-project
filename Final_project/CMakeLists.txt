cmake_minimum_required(VERSION 4.0)
project(Final_project)

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

# ---- Google Benchmark ----
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.8.4
)
FetchContent_MakeAvailable(benchmark)


add_executable(Final_project
        main.cpp
        include/core/Exchange.h
        src/core/Exchange.cpp
        include/exchanges/OKX.h
        src/Exchanges_src/OKX.cpp
        include/core/ArbitrageBot.h
        src/core/ArbitrageBot.cpp
        include/exchanges/Bybit.h
        src/Exchanges_src/Bybit.cpp
        include/core/order.h
        src/core/order.cpp
        include/market/market.h
        src/Market_src/market.cpp
        include/telegram/CommandHandler.h
        include/telegram/TelegramBot.h
        src/telegram/CommandHandler.cpp
        src/telegram/TelegramBot.cpp
        src/core/ArbitrageBot.cpp

)

target_include_directories(Final_project PRIVATE include)

add_executable(benchmarks
        benchmarks/bench_arbitrage.cpp

        src/core/Exchange.cpp
        src/Exchanges_src/OKX.cpp
        src/core/ArbitrageBot.cpp
        src/Exchanges_src/Bybit.cpp
        src/core/order.cpp
        src/Market_src/market.cpp
        src/telegram/CommandHandler.cpp
        src/telegram/TelegramBot.cpp
)

target_include_directories(benchmarks PRIVATE include)

target_link_libraries(benchmarks PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
        CURL::libcurl
        nlohmann_json::nlohmann_json
)

target_link_libraries(Final_project PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)
