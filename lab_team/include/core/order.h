#include <string>

enum class OrderType {
    BUY,
    SELL
};

class Order{
private:
    std::string Ticker_;
    std::string Exchange_;
    double buyPrice;
    double sellPrice;
    OrderType TYPE;
public:
    Order(std::string Ticker, std::string Exchange, double BP, double SP) :
    Ticker_(Ticker), Exchange_(Exchange), buyPrice(BP), sellPrice(SP){}

    double getBP() const{
        return buyPrice;
    };

    double getSP() const{
        return sellPrice;
    }

};



