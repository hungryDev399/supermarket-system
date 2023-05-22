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
        int id;
        cashier_db.printCashierDataBase();
        std::cout << "Enter the id" << std::endl;
        std::cin >> id;
        CASHIER cashier = cashier_db.returnCashierAsAnObject(id);
        // currently no validation
        std::cout << "Welcome " << cashier.get_name() << std::endl;
        startCashierPov(cashier);
    }

    if (option == 2) {
        startBigBossPov();

    }
}

void startCashierPov(CASHIER cashier) {
    int option;
    std::cout << "Welcome to your 9 to 5 job" << std::endl;
    std::cout << "Please choose an option\n 1.new order\n 2.close program" << std::endl;
    std::cin >> option;
    intgerRangeValidation(option, 1, 2);
    if (option == 1) {
        int order_option;
        
        std::vector<std::string> order_options = { "1. Add a product to the order", "2. Remove a product from the order", "3. Finish the order" };
        for (int i = 0; i < order_options.size(); i++) {
            std::cout << order_options[i] << std::endl;
        }
        std::cout << "Please choose an option" << std::endl;
        std::cin >> order_option;
        intgerRangeValidation(order_option, 1, order_options.size());
        CART cart;
        if (order_option == 1) { 
            // adding an item to the order
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
                product_db.updateProductObject(product);
                std::cout << "Do you want to add another product?\n 1. Yes\n 2. No" << std::endl;
                int add_another;
                std::cin >> add_another;
                intgerRangeValidation(add_another, 1, 2);
                cart.printProductQuantities();
                if (add_another == 2) {
					break;
				}

            }
        }
        if (order_option == 2) {
            //removing an item from the order
        }
    }
    

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
		CASHIER cashier_2("Mahmoud", 2500, 60, "01026879203");
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


