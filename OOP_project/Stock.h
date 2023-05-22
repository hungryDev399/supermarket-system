#ifndef STOCK_H
#define STOCK_H

#pragma once
#include "product_tag.h"
#include "supplier_tag.h"
//class for stock management using the product class
class Stock{
public:
	Stock ();
	void addStock(PRODUCT p, int quantity_added);
	void removeStock(PRODUCT p, int quantity_removed);
	void changeSupplier(PRODUCT p, int supplier_id);
	void PrintStockReport();
	void CheckLowStock(PRODUCT p);
};
void mainWindow();

#endif // !STOCK_H