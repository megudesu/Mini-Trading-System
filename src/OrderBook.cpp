#include <bits/stdc++.h>
#include <chrono>
#include "../include/FeedHandler.h"
#include "../include/OrderBook.h"

using namespace std;

void LimitOrderBook::addOrder(const Order& o){
    if(o.type == 'B'){
        bids[o.price].push_back(o);
        orderIndex[o.id] = {o.price, bids[o.price].size() - 1};
    }
    else if(o.type == 'S'){
        asks[o.price].push_back(o);
        orderIndex[o.id] = {o.price, asks[o.price].size() - 1};
    }
}

void LimitOrderBook::cancelOrder(const Order& o){
    if(orderIndex.count(o.id)){
        auto [price, index] = orderIndex[o.id];

        if(bids.count(price) && index < bids[price].size() && bids[price][index].id == o.id) bids[price][index].active = false;
        else if(asks.count(price) && index < asks[price].size() && asks[price][index].id == o.id) asks[price][index].active = false;

        orderIndex.erase(o.id);
    }
}

Order LimitOrderBook::matchOrder(Order o){
    if(o.type == 'B'){
        while(!asks.empty() && o.quantity > 0){
            double best_ask = asks.begin()->first;
            auto &orders = asks[best_ask];

            if(o.price < best_ask) break;
            else{
                for(auto &it : orders){
                    if(!it.active || it.quantity == 0) continue;

                    else{
                        int traded = min(o.quantity, it.quantity);

                        o.quantity -= traded;
                        it.quantity -= traded;

                        if(it.quantity == 0) it.active = false;
                        if(o.quantity == 0) break;
                    }  
                }

                bool allInactive = true;
                for(auto &it : orders){
                    if(it.active && it.quantity > 0){
                        allInactive = false;
                        break;
                    }
                }

                if(allInactive){
                    asks.erase(best_ask);
                    continue;
                }
                else break;
            }
        }
    }
    else if(o.type == 'S'){
        while(!bids.empty() && o.quantity > 0){
            double best_bid = bids.begin()->first;
            auto &orders = bids[best_bid];

            if(o.price > best_bid) break;
            else{
                for(auto &it : orders){
                    if(!it.active || it.quantity == 0) continue;

                    else{
                        int traded = min(o.quantity, it.quantity);

                        o.quantity -= traded;
                        it.quantity -= traded;

                        if(it.quantity == 0) it.active = false;
                        if(o.quantity == 0) break;
                    }
                }

                bool allInactive = true;
                for(auto &it : orders){
                    if(it.active && it.quantity > 0){
                        allInactive = false;
                        break;
                    }
                }

                if(allInactive){
                    bids.erase(best_bid);
                    continue;
                }
                else break;
            }
        }
    }
    return o;
}

void LimitOrderBook::processOrder(const Order& o){
    if(o.status == 'N'){
        Order remaining = matchOrder(o);
        if(remaining.quantity > 0) addOrder(remaining);
    }
    else if(o.status == 'C') cancelOrder(o);
}

void LimitOrderBook::printStatement(){
    cout << "------------------\n";

    if(!bids.empty()) cout << "Best bid: " << bids.begin()->first << endl;
    else cout << "Best bid: NONE" << endl;

    if(!asks.empty()) cout << "Best ask: " << asks.begin()->first << endl;
    else cout << "Best ask: NONE" << endl;

    cout << "------------------\n";
}

void LimitOrderBook::printWholeBook(){

    cout << "\n----- ORDER BOOK -----\n";

    cout << "ASKS:" << endl;

    for(auto &[price, orders] : asks){
        int total = 0;
        for(auto &o : orders) if(o.active) total += o.quantity;
        if(total > 0) cout << price << " -> " << total << endl;
    }

    cout << endl << "BIDS:" << endl;
    
    for(auto &[price, orders] : bids){
        int total = 0;
        for(auto &o : orders) if(o.active) total += o.quantity;
        if(total > 0) cout << price << " -> " << total << endl;
    }

    cout << "----------------------\n";
}

int main(){
    using namespace std::chrono;

    FeedHandler feed("../Data/Datafile.txt");
    LimitOrderBook lob;

    Order o;

    while(feed.getNextOrder(o)){
        auto start = high_resolution_clock::now();

        lob.processOrder(o);

        auto end = high_resolution_clock::now();
        auto latency = duration_cast<nanoseconds>(end - start);
        
        cout << "Latency: " << latency.count() << "ns" << endl;

        // UNCOMMENT TO CHECK BEST ASKS/BEST BIDS AFTER EVERY ORDER (affects latency)
        // lob.printStatement(); 

        // UNCOMMENT TO PRINT THE WHOLE ORDER BOOK AFTER EVERY ORDER (affects latency)
        // lob.printWholeBook();
    }

    return 0;
}