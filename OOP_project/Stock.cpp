#include "Stock.h"
#include "product_db.h"
#include "supplier.h"



Stock::Stock() {
}

void Stock::addStock(PRODUCT &p, int quantity_added) {
	p.set_quantity(p.get_quantity() + quantity_added);
	Product p1;
	p1.updateProductObject(p);
}

void Stock::removeStock(PRODUCT &p, int quantity_removed) {
	p.set_quantity(p.get_quantity() - quantity_removed);
	Product p1;
	p1.updateProductObject(p);
}

void Stock::changeSupplier(PRODUCT &p, int supplier_id) {
	p.set_product_supplier_id(supplier_id);
	Product p1;
	p1.updateProductObject(p);
}


void Stock::CheckLowStock(PRODUCT p) {
	Supplier s1;
	supplier prod_supplier = s1.returnSupplierAsAnObjectWithID(p.get_product_supplier_id());
	if (p.get_quantity() < 20) {
		cout << "WARNING! The product is low on stock." << endl
			<< "Only " << p.get_quantity() << " items of the product are available. Please contact the supplier for restock." << endl;

		cout << "The details of this supplier are: " << endl;
		prod_supplier.print_supplier();
	}
}