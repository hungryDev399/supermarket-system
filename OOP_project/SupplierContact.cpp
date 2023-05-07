/*
#include "SupplierContact.h"
using namespace std;

SupplierContact::SupplierContact() {
	this->name = "";
	this->email = "";
	this->phone = "";
	this->quantities_supplied = {};
	this->productSupplied = {};
}

SupplierContact::SupplierContact(string name, string email, string phone, vector<Product> productSupplied, vector<int> quantities_supplied) {
	this->name = name;
	this->email = email;
	this->phone = phone;
	this->productSupplied = productSupplied;
	this->quantities_supplied = quantities_supplied;
}

void SupplierContact::setName(string nametobe) {
	this->name = nametobe;
}

void SupplierContact::setEmail(string emailtobe) {
	this->email = emailtobe;
}

void SupplierContact::setPhone(string phonetobe) {
	this->phone = phonetobe;
}

void SupplierContact::setQuantitiesSupplied(vector<int> quantities_supplied_tobe) {
	this->quantities_supplied = quantities_supplied_tobe;
}

void SupplierContact::setProductSupplied(vector<Product> productSupplied_tobe) {
	this->productSupplied = productSupplied_tobe;
}

string SupplierContact::getName() {
	return this->name;
}

string SupplierContact::getEmail() {
	return this->email;
}

string SupplierContact::getPhone() {
	return this->phone;
}

vector<int> SupplierContact::getQuantitiesSupplied() {
	return this->quantities_supplied;
}

vector<Product> SupplierContact::getProductSupplied() {
	return this->productSupplied;
}

void SupplierContact::display() {
	// display the supplier contact details and display the products supplied each with its quantity
	cout << "Supplier name: " << this->name << endl;
	cout << "Supplier email: " << this->email << endl;
	cout << "Supplier phone: " << this->phone << endl;
	cout << "Products supplied: " << endl;
	for (int i = 0; i < this->productSupplied.size(); i++) {
		cout << "Product name: " << this->productSupplied[i].getName() << endl;
		cout << "Product quantity: " << this->quantities_supplied[i] << endl;
	}
}

void SupplierContact::emailSupplier() {
	// send an actual email to the supplier
}

void SupplierContact::product_request() {
	// send an email to the supplier requesting a product
}*/

