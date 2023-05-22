#include "supplier_tag.h"

supplier::supplier() {
	supplier_id = 0;
	name = "";
	address = "";
	phone_number = "";
	email = "";
}
supplier::supplier(int supplier_id, string name, string address, string phone_number, string email) {
	this->supplier_id = supplier_id;
	this->name = name;
	this->address = address;
	this->phone_number = phone_number;
	this->email = email;
	Supplier s1;
	s1.saveSupplierObject(*this);
}

// getters
int supplier::get_supplier_id() {
	return this->supplier_id;
}
string supplier::get_name() {
	return this->name;
}
string supplier::get_address() {
	return this->address;
}
string supplier::get_phone_number() {
	return this->phone_number;
}
string supplier::get_email() {
	return this->email;
}

// setters
void supplier::set_supplier_id(int supplier_id) {
	this->supplier_id = supplier_id;
}
void supplier::set_name(string name) {
	this->name = name;
}
void supplier::set_address(string address) {
	this->address = address;
}
void supplier::set_phone_number(string phone_number) {
	this->phone_number = phone_number;
}
void supplier::set_email(string email) {
	this->email = email;
}

// other functions
void supplier::print_supplier() {
	cout << "Supplier ID: " << this->supplier_id << endl;
	cout << "Name: " << this->name << endl;
	cout << "Address: " << this->address << endl;
	cout << "Phone number: " << this->phone_number << endl;
	cout << "Email: " << this->email << endl;
}

void add_supplier() {
	int supplier_id;
	string name;
	string address;
	string phone_number;
	string email;
	cout << "Enter supplier id: ";
	cin >> supplier_id;
	cout << "Enter supplier name: ";
	cin >> name;
	cout << "Enter supplier address: ";
	cin >> address;
	cout << "Enter supplier phone number: ";
	cin >> phone_number;
	cout << "Enter supplier email: ";
	cin >> email;
	supplier new_supplier(supplier_id, name, address, phone_number, email);
}

void view_supplier() {
	int supplier_id;
	cout << "Enter supplier id: ";
	cin >> supplier_id;
	Supplier s1;
	s1.returnSupplierAsAnObjectWithID(supplier_id).print_supplier();
	int choice1;
	cout << "1. Edit supplier details" << endl;
	cout << "any other number to return to the options" << endl;
	cout << "Enter your choice: ";
	cin >> choice1;
	if (choice1 == 1) {
		int choice;
		//let the user choose which field to edit
		cout << "1. Edit supplier name" << endl;
		cout << "2. Edit supplier address" << endl;
		cout << "3. Edit supplier phone number" << endl;
		cout << "4. Edit supplier email" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case(1): {
			string new_name;
			cout << "Enter new name: ";
			cin >> new_name;
			s1.returnSupplierAsAnObjectWithID(supplier_id).set_name(new_name);
			s1.saveSupplierObject(s1.returnSupplierAsAnObjectWithID(supplier_id));
			break;
		}
		case(2): {
			string address;
			cout << "Enter new address: ";
			cin >> address;
			s1.returnSupplierAsAnObjectWithID(supplier_id).set_address(address);
			s1.saveSupplierObject(s1.returnSupplierAsAnObjectWithID(supplier_id));
			break;
		}
		case(3): {
			string phone_number;
			cout << "Enter new phone number: ";
			cin >> phone_number;
			s1.returnSupplierAsAnObjectWithID(supplier_id).set_phone_number(phone_number);
			s1.saveSupplierObject(s1.returnSupplierAsAnObjectWithID(supplier_id));
			break;
		}
		case(4): {
			string email;
			cout << "Enter new email: ";
			cin >> email;
			s1.returnSupplierAsAnObjectWithID(supplier_id).set_email(email);
			s1.saveSupplierObject(s1.returnSupplierAsAnObjectWithID(supplier_id));
			break;
		}

		}
	}
	else {
		return;
	}
}
