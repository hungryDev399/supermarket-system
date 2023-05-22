#pragma once
#include <string>
#include <stdio.h>
#include <sstream>
#include <iomanip> 
#include <iostream>
#include <sqlite3.h>

#include "supplier_tag.h"
class supplier;
class Supplier {
public:
    Supplier() {
        rc = sqlite3_open("DataBase/Supplier.db", &db);
        if (rc) {
            std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            std::cout << "Opened SQLite3 database successfully" << std::endl;
        }
        const char* create_table = "CREATE TABLE IF NOT EXISTS suppliers(id INTEGER PRIMARY KEY, name TEXT, \
                               address TEXT, phone_number TEXT, email TEXT);";
        rc = sqlite3_exec(db, create_table, NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error creating Suppliers table: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    supplier returnSupplierAsAnObjectWithID(int supplier_id) {
        std::stringstream ss;
        ss << "SELECT id, name, address, phone_number, email FROM suppliers WHERE id = " << supplier_id << ";";
        std::string sql = ss.str();
        supplier s;
        rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
            supplier* s = static_cast<supplier*>(data);
            s->set_supplier_id(std::stoi(argv[0]));
            s->set_name(argv[1]);
            s->set_address(argv[2]);
            s->set_phone_number(argv[3]);
            s->set_email(argv[4]);
            return 0;
            }, &s, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error selecting data:" << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
        return s;
    }

    void saveSupplierObject(supplier s) {
        std::stringstream ss;
        ss << "INSERT INTO suppliers (id, name, address, phone_number, email) VALUES ('" << s.get_supplier_id() << "', '" << s.get_name() << "', '" << s.get_address() << "', '" << s.get_phone_number() << "', '" << s.get_email() << "');";
        std::string sql = ss.str();
        rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error inserting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    void printSupplierDataBase() {
        std::cout << "----------------------------------------------------------------------------------------------------\n";
        std::cout << "|\t\t\t\t\t  Supplier DataBase\t\t\t\t\t   |\n";
        std::cout << "|--------------------------------------------------------------------------------------------------|\n";
        std::cout << "| ID  | Name \t\t   | Address     \t| Phone Number   \t| Email          \t   |" << std::endl;
        std::cout << "|--------------------------------------------------------------------------------------------------|\n";

        const char* query = "SELECT id, name, address, phone_number, email FROM suppliers;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            std::cerr << "Error executing SQL query: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::string address(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            std::string phoneNumber(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            std::string email(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));

            std::cout << "| " << std::left << std::setw(3) << id << " | " << std::left << std::setw(18) << name << " | " << std::left << std::setw(18) << address
                << " | " << std::left << std::setw(21) << phoneNumber << " | " << std::left << std::setw(24) << email << " |" << std::endl;
        }

        std::cout << "----------------------------------------------------------------------------------------------------\n";
    }
private:
	sqlite3* db;
	char* errMsg = 0;
	int rc;
};