#pragma once
#include "pch.h"
#include <random>

using namespace std;

class PRODUCT {
public:
    PRODUCT();
    PRODUCT(string name, int quantity, int product_supplier_id, int price, bool is_pizza);
    void construct_product(string name, int quantity, int product_supplier_id, int price, bool is_pizza);
    // getters
    int get_code();
    int get_quantity();
    string get_name();
    int get_product_supplier_id();
    bool get_is_pizza();
    int get_price();

    // setters
    void set_code(int code);
    void set_name(string name);
    void set_quantity(int quantity);
    void set_product_supplier_id(int product_supplier_id);
    void set_is_pizza(bool is_pizza);
    void set_price(int price);

    // methods
    void generate_code();
    void print_product();

private:
    int code;
    string name;
    int quantity;
    int product_supplier_id;
    bool is_pizza;
    int price;
};

