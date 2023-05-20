#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

class PRODUCT {
public:
    // constructors
    PRODUCT() {
        this->code = 0;
        this->name = "";
        this->quantity = 0;
        this->product_supplier_id = 0;
        this->is_pizza = false;
        this->price = 0;
    }
    // constructor
    PRODUCT(string name, int quantity, int product_supplier_id, int price, bool is_pizza) {
        this->name = name;
        this->quantity = quantity;
        this->product_supplier_id = product_supplier_id;
        this->is_pizza = is_pizza;
        this->price = price;
        generate_code();
    }

    // getters
    int get_code() {
        return this->code;
    }
    int get_quantity() {
        return this->quantity;
    }
    string get_name() {
        return this->name;
    }
    int get_product_supplier_id() {
        return this->product_supplier_id;
    }
    bool get_is_pizza() {
        return this->is_pizza;
    }
    int get_price() {
        return this->price;
    }

    // setters
    void set_code(int code) {
        this->code = code;
    }
    void set_name(string name) {
        this->name = name;
    }
    void set_quantity(int quantity) {
        this->quantity = quantity;
    }
    void set_product_supplier_id(int product_supplier_id) {
        this->product_supplier_id = product_supplier_id;
    }
    void set_is_pizza(bool is_pizza) {
        this->is_pizza = is_pizza;
    }
    void set_price(int price) {
        this->price = price;
    }

    // other functions
    void print_product() {
        cout << "Product code: " << this->code << endl;
        cout << "Product name: " << this->name << endl;
        cout << "Product quantity: " << this->quantity << endl;
        cout << "Product supplier id: " << this->product_supplier_id << endl; // connect to supplier
        cout << "Product is pizza: " << this->is_pizza << endl;
    }

    void generate_code() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(100000, 999999);
        int new_code = distrib(gen);
        this->code = new_code;
    }

    void add_quantity(int quantity) {
        this->quantity += quantity;
    }

    void remove_quantity(int quantity) {
        this->quantity -= quantity;
    }

private:
    int code;
    string name;
    int quantity;
    int product_supplier_id;
    bool is_pizza;
    int price;
};

#endif // PRODUCT_H