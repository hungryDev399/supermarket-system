/*#include "pch.h"
#include "cart.h"
#include <vector>

//setters
void CART::set_product_codes(vector<string> product_codes) {
	this->product_codes = product_codes;
}
void CART::set_quantity(vector<int> quantity) {
	this->quantity = quantity;
}
void CART::set_user_id(string user_id) {
	this->user_id = user_id;
}
void CART::set_price(float price) {
	this->price = price;
}

//getters
vector<int> CART::get_product_codes() {
	return product_codes;
}
vector<int> CART::get_quantity() {
	return quantity;
}
string CART::get_user_id() {
	return user_id;
}
float CART::get_price() {
	return price;
}

//methods
void CART::add_item(PRODUCT* product, int quantity) {
	product_codes.push_back(product->get_code());
	this->quantity.push_back(quantity);
}
void CART::remove_item(PRODUCT* product) {
	for (int i = 0;i < product_codes.size();i++) {
		if (product_codes[i] == product->get_code()) {
			product_codes.erase(product_codes.begin() + i);
			quantity.erase(quantity.begin() + i);
		}
	}
}

//methods
void RECEIPT::create_receipt() {
	//add code here
}

void RECEIPT::print_receipt() {
	//add code here
}
void RECEIPT::edit_receipt() {
	//add code here
}
void RECEIPT::return_item() {
	//add code here
}
void RECEIPT::replace_item() {
	//add code here
}
void RECEIPT::refund() {
	//add code here
}*/