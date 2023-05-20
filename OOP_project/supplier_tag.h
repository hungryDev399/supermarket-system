//
// Created by user1 on 5/20/2023.
//


#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "product.h"
#include "Supplier.h"

class supplier {
public:
    supplier();
    supplier(int supplier_id, string name, string address, string phone_number, string email);

    // getters
    int get_supplier_id();
    string get_name();
    string get_address();
    string get_phone_number();
    string get_email();

    // setters
    void set_supplier_id(int supplier_id);
    void set_name(string name);
    void set_address(string address);
    void set_phone_number(string phone_number);
    void set_email(string email);

    // other functions
    void print_supplier();

private:
    int supplier_id;
	string name;
	string address;
	string phone_number;
	string email;
};

#endif // SUPPLIER_H

