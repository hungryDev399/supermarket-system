#pragma once

#include "pch.h"
#include "employee.h"
#include "product.h"


using namespace std;

class CART : public CASHIER {
private:
    vector<int> product_codes;
    vector<int> quantity;
    string user_id;
    float price;

public:
    //setters
    void set_product_codes(vector<string> product_codes);
    void set_quantity(vector<int> quantity);
    void set_user_id(string user_id);
    void set_price(float price);

    //getters
    vector<string> get_product_codes();
    vector<int> get_quantity();
    string get_user_id();
    float get_price();

    //methods
    void add_item(PRODUCT* product, int quantity);
    void remove_item(PRODUCT* product);
};

class RECEIPT : public CART {
public:
    //methods
    void create_receipt();
    void print_receipt();
    void edit_receipt();
    void return_item();
    void replace_item();
    void refund();
};
