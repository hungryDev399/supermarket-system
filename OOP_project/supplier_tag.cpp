#include "pch.h"
#include "supplier_tag.h"
#include "Supplier.h"
supplier::supplier() {
	supplier_id = 0;
	name = "";
	address = "";
	phone_number = "";
	email = "";
}
supplier::supplier(int supplier_id, string name, string address, string phone_number, string email) {
	this->supplier_id = supplier_id;
	this->name = name;
	this->address = address;
	this->phone_number = phone_number;
	this->email = email;
	Supplier s1;
	s1.saveSupplierObject(*this);
}

// getters
int supplier::get_supplier_id() {
	return this->supplier_id;
}
string supplier::get_name() {
	return this->name;
}
string supplier::get_address() {
	return this->address;
}
string supplier::get_phone_number() {
	return this->phone_number;
}
string supplier::get_email() {
	return this->email;
}

// setters
void supplier::set_supplier_id(int supplier_id) {
	this->supplier_id = supplier_id;
}
void supplier::set_name(string name) {
	this->name = name;
}
void supplier::set_address(string address) {
	this->address = address;
}
void supplier::set_phone_number(string phone_number) {
	this->phone_number = phone_number;
}
void supplier::set_email(string email) {
	this->email = email;
}

// other functions
void supplier::print_supplier() {
	cout << "Supplier ID: " << this->supplier_id << endl;
	cout << "Name: " << this->name << endl;
	cout << "Address: " << this->address << endl;
	cout << "Phone number: " << this->phone_number << endl;
	cout << "Email: " << this->email << endl;
}