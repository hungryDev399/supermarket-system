#include <string>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <sqlite3.h>
#include "employee.h"
#include "useful_tools.h"
#include "product.h"



class DBMS {
public:
    void getById(int id) {
        std::stringstream ss;
        ss << "SELECT * FROM users WHERE id = " << id << ";";
        std::string sql = ss.str();
        rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
            for (int i = 0; i < argc; i++) {
                std::cout << colName[i] << " = " << (argv[i] ? argv[i] : "NULL") << ", ";
            }
            std::cout << std::endl;
            return 0;
            }, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error selecting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    void printData() {
        const char* select_data = "SELECT * FROM users;";
        rc = sqlite3_exec(db, select_data, [](void* data, int argc, char** argv, char** colName) -> int {
            for (int i = 0; i < argc; i++) {
                std::cout << colName[i] << " = " << (argv[i] ? argv[i] : "NULL") << ", ";
            }
            std::cout << std::endl;
            return 0;
            }, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error selecting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    void deleteRecord(int id) {
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

protected:
    sqlite3* db;
    char* errMsg = 0;
    int rc;
};

class Cashier : public DBMS {
public: 
    Cashier() {
        rc = sqlite3_open("DataBase/Cashier.db", &db);
        if (rc) {
            std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            std::cout << "Opened SQLite3 database successfully" << std::endl;
        }
        const char* create_table = "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY,\
                                     job_title TEXT, name TEXT, status TEXT, salary REAL, age INTEGER,\
                                     permission_level INTEGER, commission REAL);";
        rc = sqlite3_exec(db, create_table, NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error creating table: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    void insertRecord(std::string job_title, std::string name, std::string status, double salary, int age, int permission_level, double commission) {
    std::stringstream ss;
    ss << "INSERT INTO users (job_title, name, status, salary, age, permission_level, commission) VALUES ('" << job_title << "', '" << name << "', '" << status << "', " << salary << ", " << age << ", " << permission_level << ", " << commission << ");";
    std::string sql = ss.str();
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error inserting data: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
           }
    }

    void updateRecordName(int id, std::string name) {
		std::stringstream ss;
		ss << "UPDATE users SET name = '" << name << "' WHERE id = " << id << ";";
		std::string sql = ss.str();
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
			std::cerr << "Error updating data: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
	}

    void updateRecordStatus(int id, std::string status) {
        std::stringstream ss;
        ss << "UPDATE users SET status = '" << status << "' WHERE id = " << id << ";";
        std::string sql = ss.str();
        rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
			std::cerr << "Error updating data: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
    }

    void updateRecordSalary(int id, double salary) {
		std::stringstream ss;
		ss << "UPDATE users SET salary = " << salary << " WHERE id = " << id << ";";
		std::string sql = ss.str();
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error updating data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    void updateRecordCommission(int id, double commission) {
		std::stringstream ss;
		ss << "UPDATE users SET commission = " << commission << " WHERE id = " << id << ";";
		std::string sql = ss.str();
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
			std::cerr << "Error updating data: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
	}

    CASHIER returnCashierAsAnObject(int id) {
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
            cashier->set_permission_level(std::stoi(argv[6]));
            cashier->set_commission(std::stod(argv[7]));
            return 0;
            }, &cashier, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error selecting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
        return cashier;
    }
    void saveCashierObject(CASHIER c) {
        std::stringstream ss;
        ss << "INSERT INTO users (job_title, name, status, salary, age, permission_level, commission) VALUES ('"\
            << c.get_job_title() << "', '"\
            << c.get_name() << "', '"\
            << c.get_status() << "', "\
            << c.get_salary() << ", "\
            << c.get_age() << ", "\
            << c.get_permission_level() << ", "\
            << c.get_commission() << ");";
		std::string sql = ss.str();
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
			std::cerr << "Error updating data: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
    }
};
 
class Products : public DBMS {
public:
    Products() {
        rc = sqlite3_open("DataBase/Products.db", &db);
        if (rc) {
            std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            std::cout << "Opened SQLite3 database successfully" << std::endl;
        }
        const char* create_table = "CREATE TABLE IF NOT EXISTS products(id INTEGER PRIMARY KEY,\
                                 name TEXT, quantity INTEGER, price INTEGER, is_pizza BOOLEAN);";
        rc = sqlite3_exec(db, create_table, NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error creating table: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    void insertRecord(std::string name, int quantity, int price, bool is_pizza) {
        std::stringstream ss;
        ss << "INSERT INTO products (name, quantity, price, is_pizza) VALUES ('" << name << "', " << quantity << ", " << price << ", " << is_pizza << ");";
        std::string sql = ss.str();
        rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error inserting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }
    void printData() {
        const char* select_data = "SELECT * FROM products;";
        rc = sqlite3_exec(db, select_data, [](void* data, int argc, char** argv, char** colName) -> int {
            for (int i = 0; i < argc; i++) {
                std::cout << colName[i] << " = " << (argv[i] ? argv[i] : "NULL") << ", ";
            }
            std::cout << std::endl;
            return 0;
            }, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error selecting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    void deleteRecord(int id) {
        std::stringstream ss;
        ss << "DELETE FROM products WHERE id = " << id << ";";
        std::string sql = ss.str();
        rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error deleting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
    }

    /*product returnProductAsAnObject(int id) {
		std::stringstream ss;
		ss << "SELECT * FROM products WHERE id = " << id << ";";
		std::string sql = ss.str();
		product p;
        rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
			product* p = static_cast<product*>(data);
			p->set_code(std::stoi(argv[0]));
			p->set_name(argv[1]);
			p->set_quantity(std::stoi(argv[2]));
			p->set_price(std::stoi(argv[3]));
			p->set_is_pizza(std::stoi(argv[4]));
			return 0;
			}, &p, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Error selecting data: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            sqlite3_close(db);
        }
        return p;
	}

    void saveProductObject(product p) {
        std::stringstream ss;
        ss << "INSERT INTO products (name, quantity, price, is_pizza) VALUES ('" << p.get_name() << "', " << p.get_quantity() << ", " << p.get_price() << ", " << p.get_is_pizza() << ");";
		std::string sql = ss.str();
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
			std::cerr << "Error updating data: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
    }*/
};






/*funcction to check if code exists
bool checkCode(int code) {
	std::stringstream ss;
	ss << "SELECT * FROM products WHERE id = " << code << ";";
	std::string sql = ss.str();
    rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
		return 0;
		}, 0, &errMsg);
    if (rc != SQLITE_OK) {
		std::cerr << "Error selecting data: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
	}
	return true;
}
*/


/*
    For employee
    + id int
    + job title string
    + name string
    + status string
    + salary double
    + age int
    + permission level int
*/

/*
class Products:public DBMS{
    public:
        Products() {
            rc = sqlite3_open("DataBase/Products.db", &db);
            if (rc) {
                std::cerr << "Error opening SQLite3 Products database: " << sqlite3_errmsg(db) << std::endl;
            }
            else {
                std::cout << "Opened Products DataBase Successfully" << std::endl;
            }
            const char* create_table = "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, name TEXT, quantity INTEGER);";
            rc = sqlite3_exec(db, create_table, NULL, 0, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "Error creating table: " << errMsg << std::endl;
                sqlite3_free(errMsg);
                sqlite3_close(db);
            }
        }

        void insertRecord(std::string name, int quantity) {
            std::stringstream ss;
            ss << "INSERT INTO users (name, quantity) VALUES ('" << name << "', " << quantity << ");";
            std::string sql = ss.str();
            rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "Error inserting data: " << errMsg << std::endl;
                sqlite3_free(errMsg);
                sqlite3_close(db);
            }
        }

        void updateRecordName(int id, std::string name) {
            std::stringstream ss;
            ss << "UPDATE users SET name = '" << name << "' WHERE id = " << id << ";";
            std::string sql = ss.str();
            rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "Error updating data: " << errMsg << std::endl;
                sqlite3_free(errMsg);
                sqlite3_close(db);
            }
        }

        void updateRecordQuantity(int id, int quantity) {
            std::stringstream ss;
            ss << "UPDATE users SET quantity = " << quantity << " WHERE id = " << id << ";";
            std::string sql = ss.str();
            rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "Error updating data: " << errMsg << std::endl;
                sqlite3_free(errMsg);
                sqlite3_close(db);
            }
        }

        std::string getRecordNameById(int id) {
            std::string name;
            std::stringstream ss;
            ss << "SELECT name FROM users WHERE id = " << id << ";";
            std::string sql = ss.str();
            rc = sqlite3_exec(db, sql.c_str(),
                [](void* data, int argc, char** argv, char** colName) -> int {
                    if (argc > 0) {
                        *((std::string*)data) = argv[0] ? argv[0] : "NULL";
                    }
                    return 0;
                }, (void*)&name, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "Error selecting data: " << errMsg << std::endl;
                sqlite3_free(errMsg);
                sqlite3_close(db);
            }
            return name;
        }

        int getRecordQuantityById(int id) {
            int quantity;
            std::stringstream ss;
            ss << "SELECT quantity FROM users WHERE id = " << id << ";";
            std::string sql = ss.str();
            rc = sqlite3_exec(db, sql.c_str(),
                [](void* data, int argc, char** argv, char** colName) -> int {
                    if (argc > 0) {
                        *((int*)data) = argv[0] ? atoi(argv[0]) : 0;
                    }
                    return 0;
                }, (void*)&quantity, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "Error selecting data: " << errMsg << std::endl;
                sqlite3_free(errMsg);
                sqlite3_close(db);
            }
            return quantity;
        }
};
*/