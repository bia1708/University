//
// Created by bia on 16/10/2023.
//

#include "Inventory.h"
#include <fstream>
#include <algorithm>
#include <iostream>

Inventory::Inventory() {
    // initialize repo with values from products.txt
    std::string name;
    int price;
    int qty;

    std::ifstream inputFile(R"(C:\Users\PC\Documents\Facultate MegaFolder\An3\PDP\Lab1\input.txt)");

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    while (!inputFile.eof()) {
        inputFile >> name >> price >> qty;
        this->addProduct(new Product(name, price, qty));
    }
    this->money = 0;
    this->money_mutex = new std::mutex();
}

// add products to inventory
void Inventory::addProduct(Product *p) {
    this->products.push_back(p);
    this->mutexes[p] = new std::mutex();
}

// sell some quantity of a single product
void Inventory::sellQty(Product *p) {
    Product* productInInventory = this->findProduct(p);
    long long addedMoney = p->getQty() * p->getPrice();

    // check if we have enough of the product
    if(productInInventory != nullptr) {
        this->money_mutex->lock();
        this->mutexes[productInInventory]->lock();
        if (productInInventory->getQty() > p->getQty()) {
            productInInventory->setQty(productInInventory->getQty() - p->getQty());
            this->money += addedMoney;
        }
        this->money_mutex->unlock();
        this->mutexes[productInInventory]->unlock();
    }
}

// method for total money persistence check
void Inventory::checkInventory(long long totalInitialValue) {
    long long currentInventoryValue = 0;
    long long currentMoney;

    //lock the money mutex
    this->money_mutex->lock();

    // lock all product mutexes before summation
    for(Product* p : this->products) {
        this->mutexes[p]->lock();
    }

    currentMoney = this->money;

    // currentInventoryValue calculation
    for(Product* p : this->products){
        currentInventoryValue += p->getQty() * p->getPrice();
    }

    //unlock the money mutex
    this->money_mutex->unlock();

    // unlock all product mutexes after summation
    for(Product* p : this->products) {
        this->mutexes[p]->unlock();
    }

    std::cout << "TOTAL: " << totalInitialValue << " CURRENT I VALUE: " << currentInventoryValue << " MONEY: " << currentMoney << "\n";
    if(totalInitialValue == currentInventoryValue + currentMoney) {
        std::cout << "Correct";
    } else {
        std::cout << "False";
    }
    std::cout << "\n";
}

// method which finds a product p in the inventory by name
Product *Inventory::findProduct(Product *p) {
    for(Product* prod : this->products) {
        if(prod->getName() == p->getName()) {
            return prod;
        }
    }
    return nullptr;
}

const std::vector<Product *> &Inventory::getProducts() const {
    return products;
}

long long Inventory::getInitialValue() {
    long long initialTotalValue = 0;

    // no locking needed here, at this point no other threads are running
    for(Product* p : this->products) {
        initialTotalValue += p->getQty() * p->getPrice();
    }
    return initialTotalValue;
}



