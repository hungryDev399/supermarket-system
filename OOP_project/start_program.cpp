#include "pch.h"
#include "employee.h"
#include "cashier_interface.h"
#include <limits>
#include "useful_tools.h"
#include "Cashier_db.h"
#include "product_tag.h"
#include "product_db.h"
#include "BigBoss_db.h"
#include "cart.h"
#include "Loyality.h"
#include "user_db.h"
//#include "Product.h"

Cashier cashier_db;
Product product_db;

void getCredentials(credentials& credential) {
    std::cout << "Enter username: ";
    std::cin >> credential.username;
    std::cout << "Enter password: ";
    std::cin >> credential.password;
    
}

void startProgram() {

     product_db.deleteProductObject(4);
    
    int option;
    std::cout << "Welcome to our SuperMarket software...." << std::endl;
    std::cout << "Please select your login role:" << '\n' << "\t[1] Login as a Cashier" << "\n\t[2] Login as a Big Boss\n" << "\t[3] Login as a Manager\n" << "Please choose (1), (2) or (3)    ";
    std::cin >> option;
    int option_count = 3;
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

        while (!cashier_db.checkIfCashierExists(id)) {
			std::cout << "Invalid ID, please try again: ";
			std::cin >> id;
		}

        std::cout << "Enter your Password: ";
        std::cin >> password;
        CASHIER cashier = cashier_db.returnCashierAsAnObject(id);

        while (password != cashier.get_password()) {
			std::cout << "Wrong password, please try again: ";
			std::cin >> password;
		}
        std::cout << "Welcome " << cashier.get_name() << std::endl;
        startCashierPov(cashier);

        // currently no validation
        
    }

    if (option == 2) {
        startBigBossPov();

    }
    if (option == 3) {
        showManagerOptions();
    }
}
int useLoyaltyPoints(int total_price);
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
    std::vector<std::string> order_options = { "\t[1] Add a product to the order", "\t[2] Remove a product from the order","\t[3] Use loyalty system" ,"\t[4] Finish the order" };
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
		//add total price instead of this random string
        int total_price = cart.get_total_price();
        int new_price = useLoyaltyPoints(total_price);
        cart.set_total_price(new_price);
	}
    if (order_option == 4) {
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

//function takes total price and returns the total price  after using loyalty points 
int useLoyaltyPoints(int total_price ) {
    std::string phone_number;
    std::cout << "Enter customer's phone number: " << std::endl;
    std::cin >> phone_number;
    while (phone_number.length() != 11 ) {
		std::cout << "Invalid phone number, please try again: " << std::endl;
		std::cin >> phone_number;
	}
    
    User user;
    bool user_exists =  user.checkIfUserExists(phone_number);
    if (!user_exists) {
        LoyaltySystem customer(phone_number);
        cout<< "User added as a Loyal Customer"<<endl;
        customer.addPointsByPurchase(total_price);
        user.saveUserObject(customer);
        std::cout << "Customer has " << customer.getLoyaltyPoints() << " points now" << endl;
    }
    else {
        LoyaltySystem customer = user.returnUserAsAnObject(phone_number);

        customer.addPointsByPurchase(total_price);
        user.updatePoints(customer);
        std::cout << "Customer has " << customer.getLoyaltyPoints() << " points" << endl;
        std::cout << "Points are translated to " << customer.pointsInMoney() << " pounds" << std::endl;
        std::cout << "choose what to do?\n\t 1. Use points\n\t 2. Add points from current purchase" << std::endl;
        int option;
        std::cin >> option;
        intgerRangeValidation(option, 1, 2);
        if (option == 1) {
            int points;
            std::cout << "Enter the number of points you want to use: " << std::endl;
            std::cin >> points;
            while (points > customer.getLoyaltyPoints()) {
                std::cout << "You don't have enough points please reenter the number of points you want to use: " << std::endl;
                std::cin >> points;
            }
            //validation of points and converting to money
            std::cout << "Are you sure you want to use " << points << " points?( 1.Yes or 2. no)" << std::endl;
            int answer;
            std::cin >> answer;
            while (answer != 1 || answer != 2) {
                std::cout << "Invalid answer, please try again: " << std::endl;
                std::cin >> answer;
            }
            if (answer == 1) {
                customer.deductLoyaltyPoints(points);
                std::cout << "You have " << customer.getLoyaltyPoints() << " points left" << std::endl;
                total_price -= customer.convertPointsToMoney(points);
            }
            else {
				std::cout << "You have " << customer.getLoyaltyPoints() << " points left" << std::endl;
			}
            user.updatePoints(customer);
            return total_price;
        }
        else {
            customer.addPointsByPurchase(total_price);
            user.updatePoints(customer);
            std::cout << "You have " << customer.getLoyaltyPoints() << " points now" << std::endl;
            return total_price;
        }
    }
}
    
    
void addItemToCart(CART& cart, Product& product_db) {
    system("CLS");
    while (true) {
        int choice, product_id, order_quantity, product_code;
        PRODUCT product;
        std::cout << "You can select product by id , code or serch for a product by name..." << std::endl;
        std::cout << "Please choose an option:\n\t[1] Select by id\n\t[2] Select by code\n\t[3] Search by name" << std::endl;
        std::cout << "Please Choose from (1), (2) or (3)    ";
        std::cin >> choice;
        if (choice == 1) {
            product_db.printProductDataBase();
            std::cout << "Enter the product id: "; 
            std::cin >> product_id;
            product = product_db.returnProductAsAnObjectWithID(product_id);
        }
        else if (choice == 2) {
            product_db.printProductDataBase();
			std::cout << "Enter the product code: ";
			std::cin >> product_code;
            product = product_db.returnProductAsAnObjectWithID(product_code);
        }
        else if (choice == 3) {
			std::cout << "Enter the product name: ";
			std::string product_name;
			std::cin >> product_name;
			product_db.printProductsByName(product_name);
			std::cout << "Enter the product id: ";
			std::cin >> product_id;
            product = product_db.returnProductAsAnObjectWithID(product_id);
		}
        

        

        std::cout << "Enter the quantity: ";
        std::cin >> order_quantity;

        intgerRangeValidation(order_quantity, 1, 100000);

        

        //add product to order
        cart.add_item(product, order_quantity);
        //std::cout << product.get_quantity() << std::endl;
        //product_db.updateProductObject(product);

        std::cout << "Do you want to add another product?\n\t[1] Yes\n\t[2] No" << std::endl;
        std::cout << "Please choose form (1) or (2)    ";
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
    BigBoss bigboss_db;
    BIGBOSS B1 = bigboss_db.returnBigBossAsAnObject(1);
    BIGBOSS* big_boss_ptr = &B1;
    
    credentials admin_credentials;

    std::string username = big_boss_ptr->getUsername();
    std::string password = big_boss_ptr->getPassword();

    getCredentials(admin_credentials);

    int trail_count = 0;
    const int max_trials = 3;
    bool logged = 1;
    while (admin_credentials.username != big_boss_ptr->getUsername() or admin_credentials.password != big_boss_ptr->getPassword()) {
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
