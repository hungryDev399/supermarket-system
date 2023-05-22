#include "product_tag.h"
#include "supplier_tag.h"
#include "Stock.h"
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

void add_product() {
	string name;
	int supplier_id;
	int quantity;
	int price;
	bool is_pizza;
	string pizza_response;
	cout << "Enter product name: ";
	cin >> name;
	cout << "Enter product quantity: ";
	cin >> quantity;
	cout << "Enter product price: ";
	cin >> price;
	cout << "Enter the supplier id: ";
	cin >> supplier_id;
	cout << "does this product happen to be an outrageously oversize pizza? (yes or no) ";
	cin >> pizza_response;

	is_pizza = (pizza_response == "yes" || pizza_response == "Yes");

	PRODUCT new_product(name, quantity, supplier_id, price, is_pizza);

	cout << "Product added successfully, " << new_product.get_name() << " code is " << new_product.get_code();
}

void view_product() {
	int product_id;
	cout << "Enter product code: ";
	cin >> product_id;

	Product p;
	PRODUCT prod = p.returnProductAsAnObjectWithCode(product_id);
	prod.print_product();
	Stock s;
	s.CheckLowStock(prod);

	int choice1;
	cout << endl << "1. Edit product details" << endl;
	cout << "2. view product supplier" << endl;
	cout << "any other number to return to options" << endl;
	cout << "Enter your choice: ";
	cin >> choice1;
	switch (choice1){
	case(1):{
		//which detail to edit
		int choice2;
		cout << "1. Edit product name" << endl;
		cout << "2. Edit product quantity" << endl;
		cout << "3. Edit product price" << endl;
		cout << "4. Edit product supplier" << endl;
		cin >> choice2;
		switch (choice2) {
			case(1): {
				string name;
				cout << "Enter new name: ";
				cin >> name;
				prod.set_name(name);
				p.saveProductObject(prod);
				break;
			}
			case(2): {
				//check add or remove quantity
				int choice3;
				cout << "1. Add quantity" << endl;
				cout << "2. Remove quantity" << endl;
				cout << "Enter your choice: ";
				cin >> choice3;
				switch (choice3) {
				case(1): {
						int quantity;
						cout << "Enter quantity to add: ";
						cin >> quantity;
						Stock s;
						s.addStock(prod, quantity);
						break;
					}
				case(2): {
						int quantity;
						cout << "Enter quantity to remove: ";
						cin >> quantity;
						Stock s;
						s.removeStock(prod, quantity);
						break;
					}
				}

				break;
			}
			case(3): {
				int price;
				cout << "Enter new price: ";
				cin >> price;
				prod.set_price(price);
				p.saveProductObject(prod);
				break;
			}
			case(4): {
				int supplier_id;
				cout << "Enter new supplier id: ";
				cin >> supplier_id;
				Stock s;
				s.changeSupplier(prod, supplier_id);
				break;
			}
			default: {
			}
			

		}
		break;
	}
	case(2): {
		Supplier s;
		s.returnSupplierAsAnObjectWithID(prod.get_product_supplier_id()).print_supplier();
		break;
		   }
	default: {
		return;
	}

	}


}
