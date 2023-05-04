#pragma once

#include "pch.h"
#include <random>
#include <limits>

std::string generateID();

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
    int total_products_sold_by_codesales;
    float commission;
    std::vector<std::string> total_products_sold_by_code;

public:
    void set_total_products_sold_by_codesales(int total_products_sold_by_codesales);
    void set_commission(float commission);
    void set_total_products_sold_by_code(std::vector<std::string> total_products_sold_by_code);

    int get_total_products_sold_by_codesales();
    float get_commission();
    std::vector<std::string> get_total_products_sold_by_code();

    CASHIER(const std::string& name, const int salary, const int age, const std::string& phone_number);

    void redeem_points(int current_points, std::string user_id);
    void add_commission();
    void AddUser(std::string phone_number);
    void check_user(std::string phone_number);
};

