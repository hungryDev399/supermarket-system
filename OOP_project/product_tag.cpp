#include "product_tag.h"


PRODUCT::PRODUCT() {
	this->code = 0;
	this->name = "";
	this->quantity = 0;
	this->product_supplier_id = 0;
	this->is_pizza = false;
	this->price = 0;
}

PRODUCT::PRODUCT(string name, int quantity, int product_supplier_id, int price, bool is_pizza) {
	this->name = name;
	this->quantity = quantity;
	this->product_supplier_id = product_supplier_id;
	this->is_pizza = is_pizza;
	this->price = price;
	generate_code();
	Product p1;
	p1.saveProductObject(*this);
}

// getters
int PRODUCT::get_code() {
	return this->code;
}
int PRODUCT::get_quantity() {
	return this->quantity;
}
string PRODUCT::get_name() {
	return this->name;
}
int PRODUCT::get_product_supplier_id() {
	return this->product_supplier_id;
}
bool PRODUCT::get_is_pizza() {
	return this->is_pizza;
}
int PRODUCT::get_price() {
	return this->price;
}

// setters
void PRODUCT::set_code(int code) {
	this->code = code;
}
void PRODUCT::set_name(string name) {
	this->name = name;
}
void PRODUCT::set_quantity(int quantity) {
	this->quantity = quantity;
}
void PRODUCT::set_product_supplier_id(int product_supplier_id) {
	this->product_supplier_id = product_supplier_id;
}
void PRODUCT::set_is_pizza(bool is_pizza) {
	this->is_pizza = is_pizza;
}
void PRODUCT::set_price(int price) {
	this->price = price;
}

// methods
void PRODUCT::generate_code() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1000, 9999);
	Product p;

	// Keep generating codes until a non-existing code is found
	while (true) {
		int code = dis(gen);
		if (!p.checkIfCodeExists(code)) {
			this->code = code;
			return;
		}
	}
}

void PRODUCT::print_product() {
	cout << "Code: " << this->code << endl;
	cout << "Name: " << this->name << endl;
	cout << "Quantity: " << this->quantity << endl;
	cout << "Product Supplier ID: " << this->product_supplier_id << endl;
	cout << "Is Pizza: " << this->is_pizza << endl;
	cout << "Price: " << this->price << endl;
}