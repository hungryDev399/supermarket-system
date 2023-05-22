#include <string>
#include <stdio.h>
#include <sstream>
#include <iomanip> 
#include <iostream>
#include <sqlite3.h>

#include "product_tag.h"
#include "product_db.h"


	Product::Product() {
		rc = sqlite3_open("DataBase/Product.db", &db);
		if (rc) {
			std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
		}
		else {
			std::cout << "Opened SQLite3 database successfully" << std::endl;
		}
		const char* create_table = "CREATE TABLE IF NOT EXISTS product(id INTEGER PRIMARY KEY, code INTEGER, \
								   name TEXT, quantity INTEGER, supplier TEXT, price REAL, is_pizza INTEGER);";
		rc = sqlite3_exec(db, create_table, NULL, 0, &errMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "Error creating Product table: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
	}

	PRODUCT Product::returnProductAsAnObjectWithID(int id) {
		std::stringstream ss;
		ss << "SELECT * FROM product WHERE id = " << id << ";";
		std::string sql = ss.str();
		PRODUCT product;
		rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
			PRODUCT* product = static_cast<PRODUCT*>(data);
			//product->set_ID(argv[0]);
			product->set_code(std::stoi(argv[1]));
			product->set_name(argv[2]);
			product->set_quantity(std::stoi(argv[3]));
			product->set_product_supplier_id(std::stoi(argv[4]));
			product->set_price(std::stod(argv[5]));
			product->set_is_pizza(std::stoi(argv[6]));
			return 0;
			}, &product, &errMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "Error selecting data: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
		return product;
	}

	PRODUCT Product::returnProductAsAnObjectWithCode(int code) {
		std::stringstream ss;
		ss << "SELECT * FROM product WHERE code = " << code << ";";
		std::string sql = ss.str();
		PRODUCT product;
		rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
			PRODUCT* product = static_cast<PRODUCT*>(data);
			//product->set_ID(argv[0]);
			product->set_code(std::stoi(argv[1]));
			product->set_name(argv[2]);
			product->set_quantity(std::stoi(argv[3]));
			product->set_product_supplier_id(std::stoi(argv[4]));
			product->set_price(std::stod(argv[5]));
			product->set_is_pizza(std::stoi(argv[6]));
			return 0;
			}, &product, &errMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "Error selecting data: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
		return product;
	}

	void Product::saveProductObject(PRODUCT p) {
		std::stringstream ss;
		ss << "INSERT INTO product (code, name, quantity, supplier, price, is_pizza) VALUES ('" << p.get_code() << "', '" << p.get_name() << "', " << p.get_quantity() << ", '" << p.get_product_supplier_id() << "', " << p.get_price() << ", " << p.get_is_pizza() << ");";
		std::string sql = ss.str();
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "Error inserting data: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
	}

	void Product::deleteProductObject(int id) {
		std::stringstream ss;
		ss << "DELETE FROM product WHERE id = " << id << ";";
		std::string sql = ss.str();
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "Error deleting data: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
	}

	void Product::updateProductObject(PRODUCT& p) {
		std::stringstream ss;
		ss << "UPDATE product SET code = '" << p.get_code() << "', name = '" << p.get_name() << "', quantity = " << p.get_quantity() << ", supplier = '" << p.get_product_supplier_id() << "', price = " << p.get_price() << ", is_pizza = " << p.get_is_pizza() << " WHERE id = " << p.get_code() << ";";
		std::string sql = ss.str();
		rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "Error updating data: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
		}
	}

	void Product::printProductDataBase() {
		std::cout << "----------------------------------------------------------------------------------------------------\n";
		std::cout << "|\t\t\t\t      Product DataBase \t\t\t\t\t           |\n";
		std::cout << "|--------------------------------------------------------------------------------------------------|\n";
		std::cout << "| Id  | Code   | Name \t\t      | Quantity  | Supplier\t| Price      \t| Is Pizza?   \t   |" << std::endl;
		std::cout << "|--------------------------------------------------------------------------------------------------|\n";

		const char* query = "SELECT id, code, name, quantity, supplier, price, is_pizza FROM product;";
		sqlite3_stmt* stmt;
		int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
		if (rc != SQLITE_OK) {
			std::cerr << "Error executing SQL query: " << sqlite3_errmsg(db) << std::endl;
			return;
		}

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			int id = sqlite3_column_int(stmt, 0);
			int code = sqlite3_column_int(stmt, 1);
			const unsigned char* name = sqlite3_column_text(stmt, 2);
			int quantity = sqlite3_column_int(stmt, 3);
			const unsigned char* supplier = sqlite3_column_text(stmt, 4);
			double price = sqlite3_column_double(stmt, 5);
			int is_pizza = sqlite3_column_int(stmt, 6);

			std::cout << "| " << std::setw(3) << id << " | " << std::setw(5) << code << " | " << std::setw(20) << name << " | "
				<< std::setw(9) << quantity << " | " << std::setw(11) << supplier << " | " << std::setw(13) << price
				<< " | " << std::setw(16) << is_pizza << " |" << std::endl;
		}

		sqlite3_finalize(stmt);
		std::cout << "----------------------------------------------------------------------------------------------------\n";
	}
	bool Product::checkIfCodeExists(int code) {
		std::stringstream ss;
		ss << "SELECT * FROM product WHERE code = " << code << ";";
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




