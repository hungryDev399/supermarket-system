#pragma once


#include <string>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <sqlite3.h>

#include "employee.h"
#include "useful_tools.h"
class CASHIER;

class Cashier {
public:
    Cashier();

    CASHIER returnCashierAsAnObject(int id);
    void saveCashierObject(CASHIER& c);
    void printCashierDataBase();
    void updateCashierObject(CASHIER c);
    void deleteCashierObject(int id);
    CASHIER getCashierObjectByPhoneNumber(std::string phoneNumber);
    bool checkIfCashierExists(int id);

private:
    sqlite3* db;
    char* errMsg = 0;
    int rc;
};


