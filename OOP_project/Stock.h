#ifndef STOCK_H

#define STOCK_H

#pragma once
#include "product_tag.h"

class Stock {

public:

	Stock();

	void addStock(PRODUCT& p, int quantity_added);

	void removeStock(PRODUCT &p, int quantity_removed);

	void changeSupplier(PRODUCT &p, int supplier_id);

	void CheckLowStock(PRODUCT p);

};



#endif // !STOCK_H