#include "pch.h"
#include "cart.h"
#include "product_tag.h"
#include "product_db.h"

void CART::add_item(PRODUCT& product, int quantity) {
	products.push_back(product);
	// check if the product exists in the map if not add it, if it is update the quantity
	std::string target = product.get_name();
	std::cout<<target<<" added to cart"<<std::endl; // "target added to cart
	if (products_quantities.find(target) == products_quantities.end())
		products_quantities[target] = quantity;
	else
		products_quantities[target] += quantity;

	product.set_quantity(product.get_quantity() - quantity);
	total_price += (product.get_price() * quantity);
}


void CART::remove_item(PRODUCT& product, int quantity_to_remove) {
	product.set_quantity(product.get_quantity() - quantity_to_remove);
	total_price -= (product.get_price() * quantity_to_remove);
	std::string product_name = product.get_name();
	products_quantities[product_name] -= quantity_to_remove;
}


std::map<std::string, int> CART::getProductQuantities() { return products_quantities; }
void CART::printProductQuantities() {
	std::cout << "Current cart" << std::endl;
	for (auto it = products_quantities.begin(); it != products_quantities.end(); it++) {
		std::cout << it->first << " " << it->second << std::endl;
	}
}

void CART::checkout(Product& product_db) {
	// looping through products and logging them in the database
	std::cout<<"The total price is: "<<total_price<<std::endl;
	for (PRODUCT product : products) {
		product_db.updateProductObject(product);
	}
}