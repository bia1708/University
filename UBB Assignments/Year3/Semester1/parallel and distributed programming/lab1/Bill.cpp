//
// Created by bia on 16/10/2023.
//

#include "Bill.h"
#include <random>
#include <iostream>

Bill::Bill(Inventory *inventory) : inventory(inventory) {
    // initialize the bill products with an arbitrary number of products from the inventory and with arbitrary quantities
    int randomNumber = 0;
    while(randomNumber == 0 || randomNumber > 10) {
        randomNumber = std::rand();
    }
    for(int i = 0; i < randomNumber; i++) {
        int randomPos = std::rand() % this->inventory->getProducts().size();
        Product* inventoryP = this->inventory->getProducts()[randomPos];

        Product* p = new Product(inventoryP->getName(), inventoryP->getPrice(), inventoryP->getQty());
        if(!this->contains(p)) {
            int randomQty = 0;

            // inventory qty numbers are between 100 and 1000 so let's have bills be the between 1 and 100
            while(randomQty == 0 || randomQty > 100) {
                randomQty = std::rand();
            }

            p->setQty(randomQty);

            // random product from the inventory with random qty
            this->products.push_back(p);
        }
    }
}

void Bill::sellProducts() {
    for (Product* p : this->products) {
        this->inventory->sellQty(p);
    }
}

void Bill::printBill() {
    std::cout << this->products.size() << "\n";
    for(Product* p : this->products) {
        std::cout << p->getName() << " " << p->getPrice() << " " << p->getQty() << "\n";
    }
}

bool Bill::contains(Product *p) {
    for(Product* prod : this->products) {
        if(p == prod) {
            return true;
        }
    }
    return false;
}
