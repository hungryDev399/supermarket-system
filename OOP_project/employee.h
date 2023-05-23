#pragma once

#include "pch.h"
#include <random>
#include <limits>
#include "useful_tools.h"
////#include "product_db.h"
//#include "product_tag.h"
//#include "Product.h"
//#include "product_tag.h"
//#include "Cashier_db.h"

//#include "Product.h"
//#include "product_tag.h"
std::string generateID();

class PRODUCT;
class EMPLOYEE {
    std::string job_title, name, ID, status;
    int salary, age, permission_level;
    std::tm* date_joined;

public:
    void set_job_title(std::string job_title);
    void set_name(std::string name);
    void set_ID(std::string ID);
    void set_status(std::string status);
    void set_salary(int salary);
    void set_age(int age);
    void set_permission_level(int permission_level);
    void setDate();


    std::string get_job_title();
    std::string get_name();
    std::string get_ID();
    std::string get_status();
    int get_salary();
    int get_age();
    int get_permission_level();
    
};


class CASHIER : public EMPLOYEE {
    std::string password, phone_number;
    int total_products_sold_by_codesales;
    float commission;
    std::vector<std::string> total_products_sold_by_code;

public:
    void set_total_products_sold_by_codesales(int total_products_sold_by_codesales);
    void set_commission(float commission);
    void set_total_products_sold_by_code(std::vector<std::string> total_products_sold_by_code);
	void set_password(std::string);
	void set_phone_number(std::string);

    int get_total_products_sold_by_codesales();
    float get_commission();
    std::string get_phone_number();
    std::string get_password();
    std::vector<std::string> get_total_products_sold_by_code();

    CASHIER(const std::string& name, const int salary, const int age, const std::string& phone_number);
    CASHIER(){}
    void construct_cashier(const std::string& name, const int salary, const int age, const std::string& phone_number);

    void redeem_points(int current_points, std::string user_id);
    void add_commission();
    void AddUser(std::string phone_number);
    void check_user(std::string phone_number);
    //void newOrder(CASHIER& cashier,Cashier& cashier_db, Product& product_db);

};

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
    
};

class BIGBOSS : public EMPLOYEE{
    std::string username, password;
    int id;

public:
    void addManager(MANAGER& manager);
    BIGBOSS();
    void addCashier(CASHIER& cashier);
    void setID(int id);
    int getID();
    void resetUsername();
    void resetPassword();
    void setUsername(std::string username);
    void setPassword(std::string password);
    void sendMessageToManager(std::string message,MANAGER manager);
    std::string getUsername();
    std::string getPassword();
    void addProduct(PRODUCT& product);

 
};