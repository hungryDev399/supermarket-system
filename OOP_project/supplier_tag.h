//
// Created by user1 on 5/20/2023.
//


#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <iostream>
#include <string>
#include "product.h"

using namespace std;

class supplier {
public:
    supplier(int supplier_id, string name, string address, string phone_number, string email) {
        this->supplier_id = supplier_id;
        this->name = name;
        this->address = address;
        this->phone_number = phone_number;
        this->email = email;
    }
    supplier() {
        supplier_id = 0;
        name = "";
        address = "";
        phone_number = "";
        email = "";
    }


    // getters
    int get_supplier_id() {
        return this->supplier_id;
    }

    string get_name() {
        return this->name;
    }

    string get_address() {
        return this->address;
    }

    string get_phone_number() {
        return this->phone_number;
    }

    string get_email() {
        return this->email;
    }

    // setters
    void set_supplier_id(int supplier_id) {
        this->supplier_id = supplier_id;
    }

    void set_name(string name) {
        this->name = name;
    }

    void set_address(string address) {
        this->address = address;
    }

    void set_phone_number(string phone_number) {
        this->phone_number = phone_number;
    }

    void set_email(string email) {
        this->email = email;
    }

    // other functions
    void print_supplier() {
        cout << "Supplier ID: " << this->supplier_id << endl;
        cout << "Supplier name:" << this->name << endl;
        cout << "Supplier address: " << this->address << endl;
        cout << "Supplier phone number: " << this->phone_number << endl;
        cout << "Supplier email: " << this->email << endl;
    }

private:
    int supplier_id;
    string name;
    string address;
    string phone_number;
    string email;


};
#endif // SUPPLIER_H

