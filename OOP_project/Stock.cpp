#include "Stock.h"

Stock::Stock() {
}

void Stock:: addStock(PRODUCT p, int quantity_added) {
	p.set_quantity(p.get_quantity() + quantity_added);
	Product p1;
	p1.saveProductObject(p);
}

void Stock::removeStock(PRODUCT p, int quantity_removed) {
	p.set_quantity(p.get_quantity() - quantity_removed);
	Product p1;
	p1.saveProductObject(p);
}

void Stock::changeSupplier(PRODUCT p, int supplier_id) {
	p.set_product_supplier_id(supplier_id);
	Product p1;
	p1.saveProductObject(p);
}

void Stock::PrintStockReport() {
	Product p1;
	p1.printProductDataBase();
}

void Stock::CheckLowStock(PRODUCT p) {
	Supplier s1;
	supplier prod_supplier =  s1.returnSupplierAsAnObjectWithID(p.get_product_supplier_id());
	if (p.get_quantity() < 20) {
		cout << "WARNING! The product is low on stock."<<endl
			 << "Only "<< p.get_quantity()<< " items of the product are available. Please contact the supplier for restock."<< endl;

		cout<< "The details of this supplier are: " << endl;
		prod_supplier.print_supplier();
	}
}
void mainWindow() {
    int choice;
    do {
        cout << "Welcome! please choose one of the following options:" << endl;
        cout << "   1. add Supplier" << endl;
        cout << "   2. add Product" << endl;
        cout << "   3. view Supplier" << endl;
        cout << "   4. view Product" << endl;
        cout << "   5. exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            add_supplier();
            break;
        }
        case 2: {
            add_product();
            break;
        }
        case 3: {
            view_supplier();
            break;
        }
        case 4: {
            view_product();
            break;
        }
        case 5: {
            break;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
        }
        }
    } while (choice != 5);
}

