//
// Created by bia on 15/10/2023.
//

#include "Product.h"

Product::Product(const std::string &name, int price, int qty) : name(name), price(price), qty(qty) {}

const std::string &Product::getName() const {
    return name;
}

void Product::setName(const std::string &name) {
    Product::name = name;
}

int Product::getPrice() const {
    return price;
}

void Product::setPrice(int price) {
    Product::price = price;
}

int Product::getQty() const {
    return qty;
}

void Product::setQty(int qty) {
    Product::qty = qty;
}
