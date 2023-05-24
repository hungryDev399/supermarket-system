#include "BigBoss_db.h"

BigBoss::BigBoss() {
	rc = sqlite3_open("DataBase/BigBoss.db", &db);
	if (rc) {
		std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		//std::cout << "Opened SQLite3 database successfully" << std::endl;
	}
	const char* create_table = "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY, username TEXT, password TEXT);";
	rc = sqlite3_exec(db, create_table, NULL, 0, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "Error creating BigBoss table: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
	}
	//saveBigBossObject();
}

void BigBoss::saveBigBossObject() {
	std::stringstream ss;
	ss << "INSERT INTO users (username, password) VALUES ('"
		<< "admin" << "', '"
		<< "admin" << "');";
	std::string sql = ss.str();
	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "Error inserting data: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
	}
}

void BigBoss::updateBigBossObject(BIGBOSS c) {
	std::stringstream ss;
	ss << "UPDATE users SET username = '" << c.getUsername() << "', password = '" << c.getPassword() << "' WHERE id = " << c.getID();
	std::string sql = ss.str();
	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "Error updating data: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
	}
}

BIGBOSS BigBoss::returnBigBossAsAnObject(int id) {
	std::stringstream ss;
	ss << "SELECT * FROM users WHERE id = '" << id << "';";
	std::string sql = ss.str();
	BIGBOSS bigboss;
	rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
		BIGBOSS* bigboss = static_cast<BIGBOSS*>(data);
		bigboss->setID(std::stoi(argv[0]));
		bigboss->setUsername(argv[1]);
		bigboss->setPassword(argv[2]);
		return 0;
		}, &bigboss, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "Error selecting data: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
	}
	return bigboss;
}

void BigBoss::printBigBossDataBase() {
	std::string sql = "SELECT * FROM users;";
	rc = sqlite3_exec(db, sql.c_str(), [](void* data, int argc, char** argv, char** colName) -> int {
		std::cout << std::setw(10) << argv[0] << std::setw(10) << argv[1] << std::setw(10) << argv[2] << std::endl;
		return 0;
		}, NULL, &errMsg);
	if (rc != SQLITE_OK) {
		std::cerr << "Error selecting data: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
	}
}