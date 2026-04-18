#ifndef order_book_h
#define order_book_h
#include "FeedHandler.h"
using namespace std;
class LimitOrderBook{
private:
    map<double, vector<Order>> asks;
    map<double,  vector<Order>, greater<double>> bids;
    unordered_map<int, pair<double, int>> orderIndex;
public:
    void processOrder(const Order& o);
    void cancelOrder(const Order& o);
    void addOrder(const Order& o);
    Order matchOrder(Order o);
    void printStatement(void);
    void printWholeBook(void);
};
#endif