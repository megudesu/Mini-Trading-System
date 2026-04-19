#include <bits/stdc++.h>
using namespace std;

int main(){
    ofstream file("../Data/Datafile.txt");

    int id = 1;
    srand(time(0));

    for(int i = 0; i < 2000; i++){
        int type = rand() % 2; // B or S
        int price = 95 + rand() % 20;
        int qty = 1 + rand() % 10;

        file << "N," << id++ << "," 
             << (type ? 'B' : 'S') << "," 
             << price << "," << qty << "\n";

        // occasional cancel
        if(i % 20 == 0 && id > 5){
            int cancel_id = 1 + rand() % (id-1);
            file << "C," << cancel_id << "\n";
        }
    }

    file.close();
}