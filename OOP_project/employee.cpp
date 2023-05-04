#include "pch.h"
#include <random>
#include <limits>
#include "employee.h"

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




