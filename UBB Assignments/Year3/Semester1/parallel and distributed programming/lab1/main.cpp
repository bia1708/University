#include <iostream>
#include <thread>
#include <unistd.h>
#include "Inventory.h"
#include "Bill.h"

void persistenceCheck(Inventory* inventory, long long totalInitialValue) {
    while(true) {
        sleep(1);
        inventory->checkInventory(totalInitialValue);
    }
}

int main() {
    Inventory* inventory = new Inventory();
    long long totalInitialValue = inventory->getInitialValue();
    std::cout << "TOTAL VALUE: " << totalInitialValue << "\n";
    std::thread threads[100];
    std::thread checkThread = std::thread(persistenceCheck, inventory, totalInitialValue);
    Bill* bills[100];

    for(int i = 0; i < 100; i++) {
        Bill* bill = new Bill(inventory);
        bills[i] = bill;
    }

    for(int i = 0; i < 100; i ++) {
        std::cout << "BILL #" << i << "\n";
        Bill* bill = bills[i];
        // thread for each bill
        threads[i] = std::thread([bill]() { bill->sellProducts(); });
    }

    for (int i = 0; i < 100; i += 2) {
        threads[i].join();
    }
    checkThread.join();
    return 0;
}
