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