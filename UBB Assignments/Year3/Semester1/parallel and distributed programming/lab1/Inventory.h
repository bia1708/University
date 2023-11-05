//
// Created by bia on 16/10/2023.
//

#ifndef LAB1_INVENTORY_H
#define LAB1_INVENTORY_H

#include "Product.h"
#include <unordered_map>
#include <mutex>
#include <vector>
#include <atomic>

class Inventory {
private:
    std::vector<Product*> products;
    std::unordered_map<Product*, std::mutex*> mutexes;
    long long money;
    std::mutex* money_mutex;

public:
    Inventory();

    void addProduct(Product* p);
    Product* findProduct(Product* p);
    void sellQty(Product* p);

    long long getInitialValue();

    const std::vector<Product *> &getProducts() const;

    void checkInventory(long long totalInitialValue);
};


#endif //LAB1_INVENTORY_H
