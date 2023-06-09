#include "pch.h"
#include <random>
#include <limits>
#include "employee.h"
#include "useful_tools.h"
#include "Cashier_db.h"
#include "product_db.h"
#include "product_tag.h"
#include "supplier_tag.h"
#include "Supplier.h"
#include "Stock.h"
class Cashier;
std::string generateID() {
    int max_int = std::numeric_limits<int>::max();
    //creating the generator engine
    std::random_device rd;
    std::mt19937 gen(rd());

    //setting the limits
    std::uniform_int_distribution<int> dis(0, max_int);
    //generating the ID
    int generated_num = dis(gen);
    std::string ID = std::to_string(generated_num);
    return ID;
}


void EMPLOYEE::set_job_title(std::string job_title) {
    this->job_title = job_title;
}

void EMPLOYEE::set_name(std::string name) {
    this->name = name;
}

void EMPLOYEE::set_ID(std::string ID) {
    this->ID = ID;
}

void EMPLOYEE::set_status(std::string status) {
    this->status = status;
}

void EMPLOYEE::set_salary(int salary) {
    this->salary = salary;
}

void EMPLOYEE::set_age(int age) {
    this->age = age;
}

void EMPLOYEE::set_permission_level(int permission_level) {
    this->permission_level = permission_level;
}

void EMPLOYEE::setDate() {
    // getting the current time
     std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
     //representing time as a timestamp
     std::time_t time = std::chrono::system_clock::to_time_t(now);
     std::tm tm;
     //converting the unix time stamp to a tm object to represent local time
     localtime_s(&tm, &time);
     //formatting the date so it is a the standard format used
     std::string date_joined = std::to_string(tm.tm_year + 1900) + "-" + std::to_string(tm.tm_mon + 1) + "-" + std::to_string(tm.tm_mday);
}

std::string EMPLOYEE::get_job_title() {
    return job_title;
}

std::string EMPLOYEE::get_name() {
    return name;
}

std::string EMPLOYEE::get_ID() {
    return ID;
}

std::string EMPLOYEE::get_status() {
    return status;
}

int EMPLOYEE::get_salary() {
    return salary;
}

int EMPLOYEE::get_age() {
    return age;
}

int EMPLOYEE::get_permission_level() {
    return permission_level;
}





//Cashier calss
void CASHIER::set_phone_number(std::string phone_numberr) {
    CASHIER::phone_number = phone_numberr;
    }
std::string CASHIER::get_phone_number() {
    return phone_number;
}

void CASHIER::set_password(std::string password) {
    CASHIER::password = password;
}
std::string CASHIER::get_password() {
    return password;
}

void CASHIER::set_total_products_sold_by_codesales(int total_products_sold_by_codesales) {
    this->total_products_sold_by_codesales = total_products_sold_by_codesales;
}

void CASHIER::set_commission(float commission) {
    this->commission = commission;
}

void CASHIER::set_total_products_sold_by_code(std::vector<std::string> total_products_sold_by_code) {
    this->total_products_sold_by_code = total_products_sold_by_code;
}

int CASHIER::get_total_products_sold_by_codesales() {
    return total_products_sold_by_codesales;
}

float CASHIER::get_commission() {
    return commission;
}

std::vector<std::string> CASHIER::get_total_products_sold_by_code() {
    return total_products_sold_by_code;
}

CASHIER::CASHIER(const std::string& name, const int salary, const int age,const std::string& phone_number) {
    set_name(name);
    set_job_title("Cashier");
    set_salary(salary);
    set_age(age);
    set_status("New");
    setDate();
    set_permission_level(1);
    set_ID(generateID());
}

void CASHIER::construct_cashier(const std::string& name, const int salary, const int age, const std::string& phone_number) {
    set_name(name);
    set_job_title("Cashier");
    set_salary(salary);
    set_age(age);
    set_status("New");
    setDate();
    set_phone_number(phone_number);
    set_permission_level(1);
    set_ID(generateID());
}

void CASHIER::redeem_points(int current_points, std::string user_id) {
    //add code here
}

void CASHIER::add_commission() {
    commission = (total_products_sold_by_codesales * 0.05) - commission;
}


 
void CASHIER::AddUser(std::string phone_number) {
        //add code here
    }
void CASHIER::check_user(std::string phone_number) {
        //add code here
    }

//void CASHIER::newOrder(CASHIER& cashier, Cashier& cashier_db, Product& product_db) {
    //add code
//}



//manager class
void MANAGER::set_Bonus(int bonus) {
	this->bonus = bonus;
}
int MANAGER::getBonus() { return bonus; }
MANAGER::MANAGER(const std::string& name, const int salary, const int age, const std::string& phone_number) {
	set_name(name);
	set_job_title("Manager");
	set_salary(salary);
	set_age(age);
	set_status("New");
	setDate();
	set_permission_level(2);
	set_ID(generateID());
}

void MANAGER::construct_manager(const std::string& name, const int salary, const int age, const std::string& phone_number) {
    set_name(name);
    set_job_title("Manager");
    set_salary(salary);
    set_age(age);
    set_status("New");
    setDate();
    set_permission_level(2);
    set_ID(generateID());
}


MANAGER::MANAGER(){}


void MANAGER::addCashier(CASHIER& cashier) {
    std::string name, phone_number;
    int salary, age;
    std::cout << "Enter the name of the cashier:" << std::endl;
    std::cin >> name;
    std::cout << "Enter the salary of the cashier:" << std::endl;
    std::cin >> salary;
    intgerRangeValidation(salary, 0, std::numeric_limits<int>::max());
    std::cout << "Enter the age of the cashier:" << std::endl;
    std::cin >> age;
    intgerRangeValidation(age, 18, 125, "Cashier is too young/old to work, please try again");

    int choice = 0;
    while (choice != 1) {
        std::cout << "Enter the phone number of the cashier:" << std::endl;
        std::cin >> phone_number;
        std::cout << "The phone number you entered is: " << phone_number << std::endl;
        std::cout << "Is the phone number correct?\n 1.Yes\n 2.No" << std::endl;

        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Cashier added successfully" << std::endl;

        }
    }
    //creating the cashier object
    cashier.construct_cashier(name, salary, age, phone_number);

}

void MANAGER::edit_product(PRODUCT prod){
    //which detail to edit
    int choice2;
    Product p1;
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
        p1.updateProductObject(prod);
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
        p1.updateProductObject(prod);
        cout << "=======================================" << endl;

        break;
    }
    case(3): {
        int price;
        cout << "Enter new price: ";
        cin >> price;
        prod.set_price(price);
        p1.updateProductObject(prod);
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
		cout << "Invalid choice" << endl;
		break;
    }


    }
}

void startProgram();
void MANAGER::view_product(){
    int product_id;
    cout << "Enter product code: ";
    cin >> product_id;
    Product p1;
    bool prod_exists= p1.checkIfCodeExists(product_id);
    if (!prod_exists) {
		cout << "Product does not exist" << endl;
        startProgram();
    }
    cout << "======================================"<<endl;
    Stock s;
    Product p;
    PRODUCT prod = p.returnProductAsAnObjectWithCode(product_id);
    int choice1;
    prod.print_product();
    s.CheckLowStock(prod);
    cout << "======================================" << endl;
    cout << endl << "1. Edit product details" << endl;
    cout << "2. view product supplier" << endl;
    cout << "any other number to return to options" << endl;
    cout << "Enter your choice: ";
    cin >> choice1;
    switch (choice1) {
    case(1): {
			edit_product(prod);
			break;
		}
    case(2): {
        Supplier s;
        s.returnSupplierAsAnObjectWithID(prod.get_product_supplier_id()).print_supplier();
           }
    default: {
        return;
           }
    }
    startProgram();
}

void MANAGER::add_supplier() {
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
    Supplier s;
    s.saveSupplierObject(new_supplier);
}
/*
void MANAGER::edit_supplier(supplier sup){
    int choice; 
    Supplier s1;

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
        sup.set_name(new_name);
        s1.updateProductObject(sub);
        break;
    }
    case(2): {
        string address;
        cout << "Enter new address: ";
        cin >> address;
        sup.set_address(address);
        s1.UpdateSupplierObject(sup);
        break;
    }
    case(3): {
        string phone_number;
        cout << "Enter new phone number: ";
        cin >> phone_number;
        sup.set_phone_number(phone_number);
        s1.UpdateSupplierObject(sup);
        break;
    }
    case(4): {
        string email;
        cout << "Enter new email: ";
        cin >> email;
        sup.set_email(email);
        s1.UpdateSupplierObject(sup);
        break;
    }

    }
}
*/
void MANAGER::view_supplier(){
    int supplier_id;
    cout << "Enter supplier id: ";
    cin >> supplier_id;
    Supplier s;
    supplier sup = s.returnSupplierAsAnObjectWithID(supplier_id);
    sup.print_supplier();
}

void MANAGER::appenedMessage(std::string message) {
    messages_recieved.push_back(message);
}
void MANAGER::showMessages() {
    for (std::string message : messages_recieved) {
		std::cout << std::endl << message << std::endl;
	}
}

//BIGBOSS

//function defenetions
void BIGBOSS::resetPassword() {
    int choice = 0;
    while (choice != 1) {
        std::string new_password;
		std::cout << "Enter the new password:" << std::endl;
		std::cin >> new_password;
		std::cout << "The new password is: " << new_password << std::endl;
		std::cout << "Is the password correct?\n 1.Yes\n 2.No" << std::endl;
		std::cin >> choice;
        if (choice == 1) {
			std::cout << "Password changed successfully" << std::endl;
			password = new_password;
		}
        else {
			std::cout << "Please try again" << std::endl;
		}
    }

}
void BIGBOSS::resetUsername() {
    std::string new_username;
	std::cout << "Enter the new username:" << std::endl;
	std::cin >> new_username;
	std::cout << "The new username is: " << new_username << std::endl;
	std::cout << "Is the username correct?\n 1.Yes\n 2.No" << std::endl;
	int choice = 0;
	std::cin >> choice;
    if (choice == 1) {
		std::cout << "Username changed successfully" << std::endl;
		username = new_username;
	}
    else {
		std::cout << "Username has not been changed" << std::endl;
	}
}
void BIGBOSS::setUsername(std::string username) {
	this->username = username;
}
void BIGBOSS::setPassword(std::string password) {
	this->password = password;
}
std::string BIGBOSS::getUsername() { return username; }
std::string BIGBOSS::getPassword() { return password; }

void BIGBOSS::sendMessageToManager(std::string message, MANAGER manager) {
    manager.appenedMessage(message);
}

BIGBOSS::BIGBOSS() {
    username = "admin";
    password = "admin";

}



void BIGBOSS::addCashier(CASHIER& cashier) {
    std::string name, phone_number;
    int salary, age;
    std::cout << "Enter the name of the cashier:" << std::endl;
    std::cin >> name;
    std::cout << "Enter the salary of the cashier:" << std::endl;
    std::cin >> salary;
    intgerRangeValidation(salary, 0, std::numeric_limits<int>::max());
    std::cout << "Enter the age of the cashier:" << std::endl;
    std::cin >> age;
    intgerRangeValidation(age, 18, 125, "Cashier is too young/old to work, please try again");

    int choice = 0;
    while (choice != 1) {
        std::cout << "Enter the phone number of the cashier:" << std::endl;
        std::cin >> phone_number;
        std::cout << "The phone number you entered is: " << phone_number << std::endl;
        std::cout << "Is the phone number correct?\n 1.Yes\n 2.No" << std::endl;

        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Cashier added successfully" << std::endl;

        }
    }
    //creating the cashier object
    cashier.construct_cashier(name, salary, age, phone_number);

}

void BIGBOSS::addManager(MANAGER& manager) {
    std::string name, phone_number;
    int salary, age;
    std::cout << "Enter the name of the Manager:" << std::endl;
    std::cin >> name;
    std::cout << "Enter the salary of the Manager:" << std::endl;
    std::cin >> salary;
    intgerRangeValidation(salary, 0, std::numeric_limits<int>::max());
    std::cout << "Enter the age of the Manager:" << std::endl;
    std::cin >> age;
    intgerRangeValidation(age, 18, 125, "Manager is too young/old to work, please try again");

    int choice = 0;
    while (choice != 1) {
        std::cout << "Enter the phone number of the Manager:" << std::endl;
        std::cin >> phone_number;
        std::cout << "The phone number you entered is: " << phone_number << std::endl;
        std::cout << "Is the phone number correct?\n 1.Yes\n 2.No" << std::endl;

        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Manager added successfully" << std::endl;
        }
        
    }

    //creating the cashier object
    manager.construct_manager(name, salary, age, phone_number);
 
}


void BIGBOSS::addProduct(PRODUCT& product) {
    std::string name;
    int quantity, price, product_supplier_id;
    bool is_pizza;
    std::cout<<"Please enter the name of the product: "<<std::endl;
    std::cin>>name;
    std::cout<<"Please enter the initial quantity of the product: "<<std::endl;
    std::cin>>quantity;
    intgerRangeValidation(quantity, 0, std::numeric_limits<int>::max());
    std::cout<<"Please enter the price of the product: "<<std::endl;
    std::cin>>price;
    intgerRangeValidation(price, 0, std::numeric_limits<int>::max());
    std::cout<<"Please enter the supplier id of the product: "<<std::endl;
    std::cin>>product_supplier_id;
    intgerRangeValidation(product_supplier_id, 0, std::numeric_limits<int>::max());
    std::cout<<"Is the product a pizza?\n 1.Yes\n 0.No"<<std::endl;
    std::cin>>is_pizza;
    while (is_pizza != 0 && is_pizza != 1) {
        std::cout << "Please enter a valid input" << std::endl;
		std::cin >> is_pizza;
    }

    int choice = 0;
    while (choice != 1) {
		std::cout << "The product you entered is: " << name << std::endl;
		std::cout << "Is the product correct?\n 1.Yes\n 2.No" << std::endl;
		std::cin >> choice;
        if (choice == 1) {
			std::cout << "Product added successfully" << std::endl;
		}
	}
	product.construct_product(name, quantity, price, product_supplier_id, is_pizza);
}

void BIGBOSS::setID(int id) {
    this->id = id;
}

int BIGBOSS::getID() {
	return this->id;
}
