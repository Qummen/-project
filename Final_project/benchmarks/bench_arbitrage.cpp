#include <benchmark/benchmark.h>
#include "core/ArbitrageBot.h"
#include "exchanges/Bybit.h"
#include "exchanges/OKX.h"

static void BM_FindArbitrage(benchmark::State& state) {
    for (auto _ : state) {
        ArbitrageBot bot;

        bot.addExchange(Bybit::create("BTCUSDT", 80.0, 100.0)); 
        bot.addExchange(OKX::create("BTCUSDT", 120.0, 140.0));

        benchmark::DoNotOptimize(bot.findArbitrage());
    }
}
BENCHMARK(BM_FindArbitrage);
