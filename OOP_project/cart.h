#include "pch.h"
#include "product_tag.h"
#include "product_db.h"

class CART :PRODUCT {
	std::vector<PRODUCT> products;
	int total_price;
	std::string user_id, cashier_id;
	std::map<std::string, int> products_quantities;
public:
	void add_item(PRODUCT& product,int quantity);
	void remove_item(PRODUCT& product, int quantity);
	std::map<std::string, int> getProductQuantities();
	void printProductQuantities();

};