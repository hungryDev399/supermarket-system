#include "user_db.h"


User::User() {
    rc = sqlite3_open("DataBase/User.db", &db);
    if (rc) {
        std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        //std::cout << "Opened SQLite3 database successfully" << std::endl;
    }
    const char* create_table = "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, \
                                phonenumber TEXT, points INTEGER);";
    rc = sqlite3_exec(db, create_table, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating Cashier table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
    }
}


LoyaltySystem User::returnUserAsAnObject(std::string phonenumber){
    std::stringstream ss;
	ss << "SELECT * FROM users WHERE phonenumber = " << phonenumber << ";";
	std::string sql = ss.str();
	LoyaltySystem user;
    rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
		LoyaltySystem* user = static_cast<LoyaltySystem*>(data);
		//user->set_id(std::stoi(argv[0]));
		user->setPhoneNumber(argv[1]);
		user->setLoyaltyPoints(std::stoi(argv[2]));
		return 0;
		}, &user, &errMsg);
    if (rc != SQLITE_OK) {
		std::cerr << "Error selecting data: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
	}
	return user;
}

/*
void User::updatePoints(LoyaltySystem c) {
    std::stringstream ss;
	ss << "UPDATE users SET points = " << c.getLoyaltyPoints() << " WHERE phonenumber = " << c.getPhoneNumber() << ";";
	std::string sql = ss.str();
	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
		std::cerr << "Error updating data: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
	}
}
*/
void User::updatePoints(LoyaltySystem c) {
    std::string sql = "UPDATE users SET points = points + ? WHERE phonenumber = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_int(stmt, 1, c.getLoyaltyPoints());
    sqlite3_bind_text(stmt, 2, c.getPhoneNumber().c_str(), -1, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);
}

void User::saveUserObject(LoyaltySystem c) {
    std::string sql = "INSERT INTO users (phonenumber, points) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, c.getPhoneNumber().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, c.getLoyaltyPoints());
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return;
    }
    sqlite3_finalize(stmt);
}


/*bool User::checkIfUserExists(std::string phone_number) {
    std::stringstream ss;
    ss << "SELECT COUNT(*) FROM users WHERE phonenumber = '" << phone_number << "';";
    std::string sql = ss.str();
    std::cout << "SQL query: " << sql << std::endl; // <-- add this line to print the SQL query
    int count = 0;
    rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
        int* countPtr = static_cast<int*>(data);
        *countPtr = std::stoi(argv[0]);
        return 0;
        }, &count, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error selecting data: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
    }
    return count > 0;
}*/
bool User::checkIfUserExists(std::string phone_number) {
    std::stringstream ss;
    ss << "SELECT COUNT(*) FROM users WHERE phonenumber = '" << phone_number << "';";
    std::string sql = ss.str();
    std::cout << "SQL query: " << sql << std::endl; // <-- add this line to print the SQL query
    bool exists = 0;
    rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
        bool* codeExistsPtr = static_cast<bool*>(data);
        *codeExistsPtr = true;
        return 0;
        }, &exists, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error selecting data: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
    }
    return exists;
}