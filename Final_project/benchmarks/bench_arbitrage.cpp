#include <benchmark/benchmark.h>

#include "core/ArbitrageBot.h"
#include "exchanges/Bybit.h"
#include "exchanges/OKX.h"

static void BM_FindArbitrage(benchmark::State& state){
    for (auto _ : state){
        ArbitrageBot bot;

        bot.addExchange(Bybit::create("BTCUSDT", 100.0, 101.0));
        bot.addExchange(OKX::create("BTCUSDT", 100.5, 100.9));

        benchmark::DoNotOptimize(bot.findArbitrage());
    }
}
BENCHMARK(BM_FindArbitrage);

BENCHMARK_MAIN();