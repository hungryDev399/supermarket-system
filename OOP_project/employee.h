#pragma once
#include "pch.h"



class EMPLOYEE {
    std::string job_title, name, ID, status;
    int salary, age, permission_level;
public:
    //setters
    void set_job_title(std::string job_title) {
        this->job_title = job_title;
    }
    void set_name(std::string name) {
        this->name = name;
    }
    void set_ID(std::string ID) {
        this->ID = ID;
    }
    void set_status(std::string status) {
        this->status = status;
    }
    void set_salary(int salary) {
        this->salary = salary;
    }
    void set_age(int age) {
        if (age < 18) {
            std::cout << "Employee is too young to work";
            return;
        }
        this->age = age;
    }
    void set_permission_level(int permission_level) {
        this->permission_level = permission_level;
    }

    //getters
    std::string get_job_title() {
        return job_title;
    }
    std::string get_name() {
        return name;
    }
    std::string get_ID() {
        return ID;
    }
    std::string get_status() {
        return status;
    }
    int get_salary() {
        return salary;
    }
    int get_age() {
        return age;
    }
    int get_permission_level() {
        return permission_level;
    }
};

//the cashier interface
class CASHIER : public EMPLOYEE {
    int total_products_sold_by_codesales;
    float commission;
    std::vector<std::string> total_products_sold_by_code;

public:
    //setters
    void set_total_products_sold_by_codesales(int total_products_sold_by_codesales) {
        this->total_products_sold_by_codesales = total_products_sold_by_codesales;
    }
    void set_commission(float commission) {
        this->commission = commission;
    }
    void set_total_products_sold_by_code(std::vector<std::string> total_products_sold_by_code) {
        this->total_products_sold_by_code = total_products_sold_by_code;
    }
    //getters
    int get_total_products_sold_by_codesales() {
        return total_products_sold_by_codesales;
    }
    float get_commission() {
        return commission;
    }
    std::vector<std::string> get_total_products_sold_by_code() {
        return total_products_sold_by_code;
    }
    //constructors
    CASHIER(int total_products_sold_by_codesales, float commission, std::vector<std::string> total_products_sold_by_code) {
        this->total_products_sold_by_codesales = total_products_sold_by_codesales;
        this->commission = commission;
        this->total_products_sold_by_code = total_products_sold_by_code;
    }
    CASHIER() {

    }
    //redeem points
    void redeem_points(int current_points, std::string user_id) {
        //add code here
    }
    //add commission
    void add_commission() {
        commission = total_products_sold_by_codesales * 0.05;
    }
    //new user
    void AddUser(std::string phone_number) {
        //add code here
    }
    void check_user(std::string phone_number) {
        //add code here
    }
};



//class BIGBOSS :public MANAGER {


//};