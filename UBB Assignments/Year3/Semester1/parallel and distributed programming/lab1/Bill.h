//
// Created by bia on 16/10/2023.
//

#ifndef LAB1_BILL_H
#define LAB1_BILL_H


#include "Product.h"
#include "Inventory.h"
#include <unordered_map>
#include <mutex>
#include <vector>

class Bill {
private:
    std::vector<Product*> products;
    Inventory* inventory;
public:
    Bill(Inventory *inventory);

public:
    void sellProducts();
    void printBill();
    bool contains(Product* p);
};


#endif //LAB1_BILL_H
