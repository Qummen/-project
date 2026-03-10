#include <string>

enum class OrderType {
    BUY,
    SELL
};

class Order{
private:
    std::string Ticker_;
    std::string Exchange_;
    double Price_;
    OrderType TYPE_;
public:
    Order(std::string Ticker, std::string Exchange, double price, OrderType t) :
    Ticker_(Ticker), Exchange_(Exchange), Price_(price), TYPE_(t){}

    double getPrice() const{
        return Price_;
    }

};


