#include "pch.h"
#include "employee.h"
#include "cashier_interface.h"
#include <limits>


bool intgerRangeValidation(int& variable, int lower_bound, int upperboud, int num_of_tials) {
    int trials = 0;
    bool success = 1;
    while ((variable < lower_bound || variable > upperboud)) {
        std::cout << "Input out of range please try again:" << std::endl;
        std::cin >> variable;
        if (trials <= num_of_tials) {
            success = 0;
            break;
        }
        trials++;
    }
    return success;
}

void intgerRangeValidation(int& variable, int lower_bound, int upperboud) {

    bool success = 1;
    while ((variable < lower_bound || variable > upperboud)) {
        std::cout << "Input out of range please try again:" << std::endl;
        std::cin >> variable;
    }

}

void intgerRangeValidation(int& variable, int lower_bound, int upperboud,std::string&& message) {

    bool success = 1;
    while ((variable < lower_bound || variable > upperboud)) {
        std::cout << message << std::endl;
        std::cin >> variable;
    }

}


void intgerRangeValidation(int& variable, int lower_bound, int upperboud, std::string& message) {

    bool success = 1;
    while ((variable < lower_bound || variable > upperboud)) {
        std::cout << message << std::endl;
        std::cin >> variable;
    }

}

void getCredentials(credentials& credential) {
    std::cout << "Enter username: "<< std::endl;
    std::cin >> credential.username;
    std::cout << "Enter password: " << std::endl;
    std::cin >> credential.password;
}

void startProgram() {
    int option;
    std::cout << "Choose an option" << '\n' << "1. Login as a Cashier" << "\n2. Login as a Big Boss\n";
    std::cin >> option;
    int option_count = 2;
    while (option<0 || option>option_count) {
        std::cout << "Invalid option, please try again"<<std::endl;
        std::cin >> option;
    }

    if (option == 1) {
        std::cout << "Under construction" << std::endl;
        return;
    }

    if (option == 2) {
        startBigBossPov();

    }
}

void startBigBossPov() {
    credentials admin_credentials;
    std::string* username = &admin_credentials.username;
    std::string* password = &admin_credentials.password;
    getCredentials(admin_credentials);
    int trail_count = 0;
    const int max_trials = 3;
    bool logged = 1;
    while (*username != admin_username or *password != admin_pass) {
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
        showOptions();
        
    }
    else
        std::cout << "Too much trials" << std::endl;
}

void showOptions() {
    std::vector<std::string> options = { "1. Add an employee" };
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


    switch (option) {
    case 1:
        addEmployee();
        break;
    
    }
}
void addEmployee() {
    std::vector<std::string> options = { "1. Add a Cashier", "2. Add a Manager", "3. Add another Big Boss"};

    
    //showing avaialble options
    for (std::string o : options) {
        std::cout << o << std::endl;
    }
    
    //getting the user's desired option
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

    //A switch case because other options were too sophisticated
    switch (option) {
    case 1:
        newCashier();
        break;

    }


}

void newCashier() {
    std::string name,phone_number;
    int salary,age;
    std::cout << "Enter the name of the cashier:" << std::endl;
    std::cin >> name;
    std::cout << "Enter the salary of the cashier:" << std::endl;
    std::cin >> salary;
    intgerRangeValidation(salary,0, std::numeric_limits<int>::max());
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
            std::cout << "Cahier added successfully" << std::endl;
        }
    }
    //creating the cashier object
    CASHIER cashier(name, salary, age,phone_number);
    std::cout << cashier.get_age()<<std::endl;

    //log the cashier
    // add logging code
    bool chose = 1;
    do {
        std::cout << "Choose were you want to get back to:\n 1. Start\n 2.Big Boss menu\n 3. Add another employee\n 4.End the program" << std::endl;
        int back;
        std::cin >> back;
        if (back == 1) {
            chose = 1;
            startProgram();
        }
        if (back == 2) {
            chose = 1;
            startBigBossPov();
        }
        if (back == 3) {
            chose = 1;
            addEmployee();
        }
        if (back == 4) {
            chose = 1;
        }
        else
            std::cout << "Incorrect option" << std::endl;
    } while (!chose);
}