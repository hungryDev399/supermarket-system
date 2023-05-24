#include <string>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <sqlite3.h>

#include "employee.h"
#include "useful_tools.h"
#include "Cashier_db.h"

Cashier::Cashier() {
        rc = sqlite3_open("DataBase/Cashier.db", &db);
        if (rc) {
            std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            //std::cout << "Opened SQLite3 database successfully" << std::endl;
        }
        const char* create_table = "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, \
                                   job_title TEXT, name TEXT, status TEXT, salary REAL, age INTEGER, \
                                   phone_number TEXT, permission_level INTEGER, commission REAL, \
                                   password TEXT);";
        rc = sqlite3_exec(db, create_table, NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error creating Cashier table: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    CASHIER Cashier::returnCashierAsAnObject(int id) {
        std::stringstream ss;
        ss << "SELECT * FROM users WHERE id = " << id << ";";
        std::string sql = ss.str();
        CASHIER cashier;
        rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
            CASHIER* cashier = static_cast<CASHIER*>(data);
            cashier->set_ID(argv[0]);
            cashier->set_job_title(argv[1]);
            cashier->set_name(argv[2]);
            cashier->set_status(argv[3]);
            cashier->set_salary(std::stod(argv[4]));
            cashier->set_age(std::stoi(argv[5]));
            cashier->set_phone_number(argv[6]);
            cashier->set_permission_level(std::stoi(argv[7]));
            cashier->set_commission(std::stod(argv[8]));
            cashier->set_password(argv[9]);
            return 0;
            }, &cashier, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error selecting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
        return cashier;
    }
    void Cashier::saveCashierObject(CASHIER& c) {
        std::stringstream ss;
        ss << "INSERT INTO users (job_title, name, status, salary, age, phone_number, permission_level, commission, password) VALUES ('"
            << c.get_job_title() << "', '"
            << c.get_name() << "', '"
            << c.get_status() << "', "
            << c.get_salary() << ", "
            << c.get_age() << ", '"
            << c.get_phone_number() << "', "
            << c.get_permission_level() << ", "
            << c.get_commission() << ", '"
            << c.get_password() << "');";
        std::string sql = ss.str();
        rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error inserting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }
    void Cashier::printCashierDataBase() {
        std::cout << "----------------------------------------------------------------------------------------------------\n";
        std::cout << "|\t\t\t\t      Cashier DataBase \t\t\t\t\t           |\n";
        std::cout << "|--------------------------------------------------------------------------------------------------|\n";
        std::cout << "| Id  | Name \t\t   | Salary    \t| Commission   \t| Phone Number  \t| Permission Level |" << std::endl;
        std::cout << "|--------------------------------------------------------------------------------------------------|\n";

        const char* query = "SELECT id, name, salary, commission, phone_number, permission_level FROM users;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            std::cerr << "Error executing SQL query: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            double salary = sqlite3_column_double(stmt, 2);
            double commission = sqlite3_column_double(stmt, 3);
            std::string phoneNumber(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            int permissionLevel = sqlite3_column_int(stmt, 5);

            std::cout << "| " << std::left << std::setw(3) << id << " | " << std::left << std::setw(18) << name << " | " << std::left << std::setw(10) << salary
                << " | " << std::left << std::setw(13) << commission << " | " << std::left << std::setw(22) << phoneNumber << "|" << std::left << std::setw(16) << permissionLevel << "  |" << std::endl;
        }

        std::cout << "----------------------------------------------------------------------------------------------------\n";
    }

    void Cashier::updateCashierObject(CASHIER c) {
        std::stringstream ss;
        ss << "UPDATE users SET job_title = '" << c.get_job_title() << "', name = '" << c.get_name() << "', status = '" << c.get_status() << "', salary = " << c.get_salary() << ", age = " << c.get_age() << ", phone_number = '" << c.get_phone_number() << "', permission_level = " << c.get_permission_level() << ", commission = " << c.get_commission() << ", password = '" << c.get_password() << "' WHERE id = " << c.get_ID() << ";";
        std::string sql = ss.str();
        rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error updating data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }


    void Cashier::deleteCashierObject(int id) {
        std::stringstream ss;
        ss << "DELETE FROM users WHERE id = " << id << ";";
        std::string sql = ss.str();
        rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error deleting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    CASHIER Cashier::getCashierObjectByPhoneNumber(std::string phoneNumber) {
        std::stringstream ss;
        ss << "SELECT * FROM users WHERE phone_number = '" << phoneNumber << "';";
        std::string sql = ss.str();
        CASHIER cashier;
        rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
            CASHIER* cashier = static_cast<CASHIER*>(data);
            cashier->set_ID(argv[0]);
            cashier->set_job_title(argv[1]);
            cashier->set_name(argv[2]);
            cashier->set_status(argv[3]);
            cashier->set_salary(std::stod(argv[4]));
            cashier->set_age(std::stoi(argv[5]));
            cashier->set_phone_number(argv[6]);
            cashier->set_permission_level(std::stoi(argv[7]));
            cashier->set_commission(std::stod(argv[8]));
            cashier->set_password(argv[9]);
            return 0;
            }, &cashier, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error selecting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
        return cashier;
    }

    bool Cashier::checkIfCashierExists(int id) {
            std::stringstream ss;
            ss << "SELECT * FROM users WHERE id = " << id << ";";
            std::string sql = ss.str();
            bool codeExists = false;
            rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
                bool* codeExistsPtr = static_cast<bool*>(data);
                *codeExistsPtr = true;
                return 0;
                }, &codeExists, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "Error selecting data: " << errMsg << std::endl;
                sqlite3_free(errMsg);
                sqlite3_close(db);
            }
            return codeExists;
        }
    