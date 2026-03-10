#include <string>
#include <vector>
#include <random>
#include <iostream>

class Market{
private:
    std::vector<std::string> Tickers_ = {"BTC", "ETH", "SOL", "USDT", "XRP"};
    std::string Exchange_Bybit;
    std::string Exchange_OKX;
    std::vector<double> Prices_Bybit;
    std::vector<double> Prices_OKX;
public:
    Market() = default;

    void GenerateBybit(std::string exchange){
        if(exchange == "Bybit"){

            Exchange_Bybit = exchange;

            std::mt19937_64 rng(std::random_device{}());

            std::uniform_real_distribution<double> dist(0.0, 1000000.0);


            for (int i = 0; i < 5; ++i) {
                Prices_Bybit.emplace_back(dist(rng));
            }
        }

        if(exchange != "Bybit"){
            Exchange_OKX = exchange;
        }
    }

    void GenerateOKX(std::string exchange){
        if(exchange == "OKX"){

            Exchange_OKX = exchange;

            std::mt19937_64 rng(std::random_device{}());

            std::uniform_real_distribution<double> dist(0.0, 1000000.0);


            for (int i = 0; i < 5; ++i) {
                Prices_OKX.emplace_back(dist(rng));
            }
        }

        if(exchange != "OKX"){
            Exchange_Bybit = exchange;
        }

    }

    void printBybit() const{
        std::cout << "BTC price: " << Prices_Bybit[0];
        std::cout << "ETH price: " << Prices_Bybit[1];
        std::cout << "SOL price: " << Prices_Bybit[2];
        std::cout << "USDT price: " << Prices_Bybit[3];
        std::cout << "XRP price: " << Prices_Bybit[4];
    }

    void printOKX() const{
        std::cout << "BTC price: " << Prices_OKX[0];
        std::cout << "ETH price: " << Prices_OKX[1];
        std::cout << "SOL price: " << Prices_OKX[2];
        std::cout << "USDT price: " << Prices_OKX[3];
        std::cout << "XRP price: " << Prices_OKX[4];
    }


    ~Market() = default;
};