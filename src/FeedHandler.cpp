#include <bits/stdc++.h>
#include "../Header/FeedHandler.h"
using namespace std;

FeedHandler::FeedHandler(const std::string& filename){
    data.open(filename);

    if(!data.is_open()) cout << "Error opening file" << endl;
}


bool FeedHandler::getNextOrder(Order &order){
    string line;

    if(!getline(data, line)) return false;

    stringstream ss(line);
    string token;

    // Read type (N or C)
    getline(ss, token, ',');
    
    if(token == "N"){
        order.status = 'N';

        // ID
        getline(ss, token, ',');
        order.id = stoi(token);

        // Type
        getline(ss, token, ',');
        order.type = token[0];

        // Price
        getline(ss, token, ',');
        order.price = stod(token);

        // Quantity
        getline(ss, token, ',');
        order.quantity = stoi(token);

    } 
    else if(token == "C"){
        order.status = 'C';

        // ID only
        getline(ss, token, ',');
        order.id = stoi(token);

        // Rest not needed
        order.type = 'X';
        order.price = 0;
        order.quantity = 0;
    }

    return true;
}

// int main(){
//     FeedHandler feed("../Data/Datafile.txt");

//     Order o;

//     while(feed.getNextOrder(o)){
//         if(o.status == 'N'){
//             cout << "NEW: " << o.id << " "
//                 << o.type << " "
//                 << o.price << " "
//                 << o.quantity << endl;
//         } 
//         else cout << "CANCEL: " << o.id << endl;
//     }
    
//     return 0;
// }