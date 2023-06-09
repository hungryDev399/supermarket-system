#pragma once
#include <string>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <sqlite3.h>

#include "Loyality.h"

class User {
public:
    User();
    void saveUserObject(LoyaltySystem c);
    LoyaltySystem returnUserAsAnObject(std::string phone_number);
    void updatePoints(LoyaltySystem c);
    bool checkIfUserExists(std:: string phone_number);

    

private:
    sqlite3* db;
    char* errMsg = 0;
    int rc;
};