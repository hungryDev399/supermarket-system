#include "pch.h"
#include "employee.h"
#include "cashier_interface.h"
#include <limits>
#include "useful_tools.h"
#include "Cashier_db.h"
#include "product_tag.h"
#include "product_db.h"
#include "cart.h"
//#include "Product.h"

Cashier cashier_db;
Product product_db;

void getCredentials(credentials& credential) {
    std::cout << "Enter username: "<< std::endl;
    std::cin >> credential.username;
    std::cout << "Enter password: " << std::endl;
    std::cin >> credential.password;
    
}

void startProgram() {

     product_db.deleteProductObject(4);
    
    int option;
    std::cout << "Choose an option:" << '\n' << "\t1. Login as a Cashier" << "\n\t2. Login as a Big Boss\n" << "Please Enter your Choice: ";
    std::cin >> option;
    int option_count = 2;
    while (option<0) {
        std::cout << "Invalid option, please try again"<<std::endl;
        std::cin >> option;
    }

    if (option == 1) {
        system("CLS");
        std::cout << "Hi their, please enter market staff login credentials" << std::endl;
        int id;
        std::string password;
        //cashier_db.printCashierDataBase();
        std::cout << "Enter your ID: " ;
        std::cin >> id;
        std::cout << "Enter your Password: ";
        std::cin >> password;
        CASHIER cashier = cashier_db.returnCashierAsAnObject(id);
        if (password == cashier.get_password()) {
            std::cout << "Welcome " << cashier.get_name() << std::endl;
            startCashierPov(cashier);
        }
        else {
            std::cout << "Wrong password" << std::endl;
        }
        // currently no validation
        
    }

    if (option == 2) {
        startBigBossPov();

    }
    if (option == 3) {
        showManagerOptions();
    }
}

void addItemToCart(CART& cart, Product& product_db);
void removeItemFromCart(CART& cart, Product& product_db);
void newOrder(CART& cart);
void startCashierPov(CASHIER& cashier) {
    int option;
    system("CLS");
    std::cout << "Welcome <"<< cashier.get_name() << "> to Cashier panel :-)" << std::endl;
    std::cout << "Please choose what do you want to do....\n\t[1] new order\n\t[2] close program" << "\nPlease choose (1) or (2)    ";
    std::cin >> option;
    intgerRangeValidation(option, 1, 2);
    CART cart;
    if (option == 1) {
        
        newOrder(cart);
        
    }
    

}

void newOrder(CART& cart) {
    int order_option;
    system("CLS");
    std::cout << "Welcome to oreder mangment section..." << std::endl;
    std::vector<std::string> order_options = { "\t[1] Add a product to the order", "\t[2] Remove a product from the order", "\t[3] Finish the order" };
    for (int i = 0; i < order_options.size(); i++) {
        std::cout << order_options[i] << std::endl;
    }
    std::cout << "Please choose an option:  ";
    std::cin >> order_option;
    intgerRangeValidation(order_option, 1, order_options.size());
    
    if (order_option == 1) {
        // adding an item to the order
        addItemToCart(cart, product_db);

    }// validations required
    if (order_option == 2) {
		// removing an item from the order
		removeItemFromCart(cart, product_db);
	}
    if (order_option == 3) {
        cart.checkout(product_db);
    }

    std::cout << "Chosse an option:\n 1. continue\n 2. exit" << std::endl;
    int end_option;
    std::cin >> end_option;
    intgerRangeValidation(end_option, 1, 3);
    if (end_option == 1) {
		newOrder(cart);
	}


}
void addItemToCart(CART& cart, Product& product_db) {
    while (true) {
        product_db.printProductDataBase();
        int product_id, order_quantity;
        std::cout << "Enter the product id" << std::endl;
        std::cin >> product_id;
        std::cout << "Enter the quantity" << std::endl;
        std::cin >> order_quantity;
        intgerRangeValidation(order_quantity, 1, 100000);
        PRODUCT product = product_db.returnProductAsAnObjectWithID(product_id);
        //add product to order
        cart.add_item(product, order_quantity);
        //std::cout << product.get_quantity() << std::endl;
        //product_db.updateProductObject(product);
        std::cout << "Do you want to add another product?\n 1. Yes\n 2. No" << std::endl;
        int add_another;
        std::cin >> add_another;
        intgerRangeValidation(add_another, 1, 2);
        cart.printProductQuantities();
        if (add_another == 2) {
            return;
        }
    }
    newOrder(cart);
}
void removeItemFromCart(CART& cart, Product& product_db) {
    while (true) {
        std::cout << std::endl;
		cart.printProductQuantities();
        std::cout << std::endl;

		int product_id, order_quantity;
		std::cout << "Enter the product id" << std::endl;
		std::cin >> product_id;
		std::cout << "Enter the quantity" << std::endl;
		std::cin >> order_quantity;
		intgerRangeValidation(order_quantity, 1, 100000);
		PRODUCT product = product_db.returnProductAsAnObjectWithID(product_id);
		//add product to order
		cart.remove_item(product, order_quantity);
		//product_db.updateProductObject(product);
		std::cout << "Do you want to remove another product?\n 1. Yes\n 2. No" << std::endl;
		int add_another;
		std::cin >> add_another;
		intgerRangeValidation(add_another, 1, 2);
		cart.printProductQuantities();
        if (add_another == 2) {
            return;
		}
	}
    newOrder(cart);
}




void startBigBossPov() {
    BIGBOSS* big_boss_ptr = new BIGBOSS();
    credentials admin_credentials;
    std::string* username = &admin_credentials.username;
    std::string* password = &admin_credentials.password;
    getCredentials(admin_credentials);
    int trail_count = 0;
    const int max_trials = 3;
    bool logged = 1;
    while (*username != big_boss_ptr->getUsername() or *password != big_boss_ptr->getPassword()) {
        trail_count++;
        std::cout << "Incorrect username or password" << std::endl;
        getCredentials(admin_credentials);
        if (trail_count > max_trials) {
            break;
            logged = 0;
        }
    }
    if (logged) {
        std::cout << "Login successful" << std::endl;
        showBigBossOptions(big_boss_ptr);
        
    }
    else {
        std::cout << "Too much trials" << std::endl;
        delete big_boss_ptr;
    }
}

void showBigBossOptions(BIGBOSS* big_boss_ptr) {
    std::vector<std::string> options = { "1. Add a Cashier", "2. Add a Manager","3.Add new product"};
    for (std::string o : options) {
        std::cout << o << std::endl;
    }
    int option;
    std::cin >> option;
    bool succeeded = intgerRangeValidation(option, 1, options.size(), 6);

    //giving the user the option to go back
    while (!succeeded) {
        std::cout << "You are out of trials" << std::endl;
        std::cout << "Choose were you want to get back to:\n 1. Start\n 2.Big Boss menu" << std::endl;
        int back;
        std::cin >> back;
        if (back == 1) {
            succeeded = 1;
            startProgram();
        }
        if (back == 2) {
            succeeded = 1;
            startBigBossPov();
        }
        else
            std::cout << "Incorrect option" << std::endl;
    }


    /*delete cashier by id
    update by object*/
    /*return product id
    return product by code
    delete by id
    check if code exists
    update by object
    upd*/
    
    if (option == 1) {
        CASHIER cashier;
		big_boss_ptr->addCashier(cashier);
        std::cout << cashier.get_phone_number()<<std::endl;
		//log int the cashier in the database
        cashier_db.saveCashierObject(cashier);
	}
    if (option == 2) {
        MANAGER manager;
		big_boss_ptr->addManager(manager);
		//add construction
	}


    if (option == 3) {
        bool again = 1;
        while (again) {
            PRODUCT product;
            big_boss_ptr->addProduct(product);
            product_db.saveProductObject(product);
            product_db.printProductDataBase();
            std::cout << "Do you want to add another product? 1.yes 2.no" << std::endl;
            int again_option;
            std::cin >> again_option;
            intgerRangeValidation(again_option, 1, 2);
            if (again_option == 2) {
				again = 0;
			}

        }
    }
    

	
}

//utilize manager class from here 
/*
class MANAGER : public EMPLOYEE {
    int bonus;
    std::vector<std::string> messages_recieved;
public:
    void set_Bonus(int bonus);
    void appenedMessage(std::string message);
    void showMessages();
    int getBonus();
    void addCashier(CASHIER& cashier);
    void construct_manager(const std::string& name, const int salary, const int age, const std::string& phone_number);
    void edit_product(PRODUCT prod);
    void view_product();
    void add_supplier();
    // void edit_supplier();
    void view_supplier();
    MANAGER();
    MANAGER(const std::string& name, const int salary, const int age, const std::string& phone_number);

};*/
//utilize manager class from the previous comments

void showManagerOptions() {
    MANAGER manager;
    std::cout<< "Welcome to the manager menu" << std::endl;
    std::vector<std::string> options = { "1. View and edit a product", "2. View supplier","3. Add new supplier" };
    for (std::string o : options) {
		std::cout << o << std::endl;
	}

    int option;
    std::cin >> option;
    bool succeeded = intgerRangeValidation(option, 1, options.size(), 6);

    //giving the user the option to go back
    while (!succeeded) {
        std::cout<<"You are out of trials"<<std::endl;
        std::cout << "Press on any number to go back";
        int back;
        std::cin >> back;
        startProgram();
    }

    if (option == 1) {
        manager.view_product();
    }
    if (option == 2) {
		manager.view_supplier();
	}
    if (option == 3) {
		manager.add_supplier();
	}

}
