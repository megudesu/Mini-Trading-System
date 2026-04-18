#ifndef FeedHandler_h
#define FeedHandler_h

#include <string>
#include <fstream>

struct Order{
    int id;
    char status;
    char type;
    int price;
    int quantity;
    bool active = true;
};

class FeedHandler{
private:
    std::ifstream data;

public:
    FeedHandler(const std::string& filename);

    bool getNextOrder(Order &order);
};

#endif