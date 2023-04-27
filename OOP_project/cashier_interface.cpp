#include "pch.h"
#include "employee.h"
#include "cashier_interface.h"



void getCredentials(credentials& credential) {
    std::cout << "Enter username: ";
    std::cin >> credential.username;
    std::cout << "Enter password: ";
    std::cin >> credential.password;
}

void startCashierPov() {
    int option;
    std::cout << "Choose an option" << '\n' << "1. Login as a Cashier" << "2. Login as admin";
    std::cin >> option;
    int option_count = 2;
    while (option<0 || option>option_count) {
        std::cout << "Invalid option, please try again";
        std::cin >> option;
    }
    if (option == 1) {
        std::cout << "Under construction" << std::endl;
        return;
    }

    if (option == 2) {
        credentials admin_credentials;
        std::string* username = &admin_credentials.username;
        std::string* password = &admin_credentials.password;
        getCredentials(admin_credentials);
        while (*username != admin_username or *password != admin_pass) {
            std::cout << "Incorrect username or password" << std::endl;
            getCredentials(admin_credentials);
        }
        std::cout << "Login successful" << std::endl;
    }
}
