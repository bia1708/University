//
// Created by bia on 15/10/2023.
//

#ifndef LAB1_PRODUCT_H
#define LAB1_PRODUCT_H


#include <string>

class Product {
private:
    std::string name;
    int price;
    int qty;

public:
    Product(const std::string &name, int price, int qty);

    const std::string &getName() const;

    void setName(const std::string &name);

    int getPrice() const;

    void setPrice(int price);

    int getQty() const;

    void setQty(int qty);
};


#endif //LAB1_PRODUCT_H
