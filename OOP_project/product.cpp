#include "pch.h"
#include "product.h"

using namespace std;

//setters
void PRODUCT::set_product_code(string product_code) {
    this->product_code = product_code;
}
void PRODUCT::set_name(string name) {
    this->name = name;
}
void PRODUCT::set_brand(string brand) {
    this->brand = brand;
}
void PRODUCT::set_category(string category) {
    this->category = category;
}
void PRODUCT::set_stock_level(int stock_level) {
    this->stock_level = stock_level;
}
void PRODUCT::set_price(float price) {
    this->price = price;
}
void PRODUCT::set_is_pizza(bool is_pizza) {
    this->is_pizza = is_pizza;
}

//getters
string PRODUCT::get_product_code() const {
    return product_code;
}
string PRODUCT::get_name() const {
    return name;
}
string PRODUCT::get_brand() const {
    return brand;
}
string PRODUCT::get_category() const {
    return category;
}
int PRODUCT::get_stock_level() const {
    return stock_level;
}
float PRODUCT::get_price() const {
    return price;
}
bool PRODUCT::get_is_pizza() const {
    return is_pizza;
}

//constructor
PRODUCT::PRODUCT() {
    generatecode();
}

//methods
void PRODUCT::generatecode() {
    product_code = to_string(rand() % 100000);
}
