#include <string>
#include <vector>
#include <random>
#include <iostream>

class Market{
private:
    std::vector<std::string> tickers_ = {"BTC", "ETH", "SOL", "USDT", "XRP"};
    std::vector<double> pricesBybit_;
    std::vector<double> pricesOkx_;

    static void fillRandom(std::vector<double>& out, std::size_t n){
        std::mt19937_64 rng(std::random_device{}());
        std::uniform_real_distribution<double> dist(0.0, 1'000'000.0);

        out.clear();

        out.resize(n);
        for (std::size_t i = 0; i < n; ++i)
            out[i] = dist(rng);
    }\
public:
    Market() = default;

    void generateBybit(){
        fillRandom(pricesBybit_, tickers_.size());
    }

    void generateOKX(){
        fillRandom(pricesOkx_, tickers_.size());
    }

    void printBybit() const{
        if (pricesBybit_.size() != tickers_.size()) {
            std::cout << "Bybit prices are not generated yet\n";
            return;
        }
        for (std::size_t i = 0; i < tickers_.size(); ++i) {
            std::cout << tickers_[i] << " price: " << pricesBybit_[i] << "\n";
        }
    }

    void printOKX() const{
        if (pricesOkx_.size() != tickers_.size()) {
            std::cout << "OKX prices are not generated yet\n";
            return;
        }
        for (std::size_t i = 0; i < tickers_.size(); ++i) {
            std::cout << tickers_[i] << " price: " << pricesOkx_[i] << "\n";
        }
    }
};