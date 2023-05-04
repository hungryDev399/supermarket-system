#pragma once
#include "pch.h"
struct credentials {
    std::string username, password;
};
extern std::string admin_pass;
extern std::string admin_username;
typedef void (*functio_ptr)();

void getCredentials(credentials& credential);
void startProgram();
void startBigBossPov();
void addEmployee();
void newCashier();
void showOptions();
bool intgerRangeValidation(int& variable, int lower_bound, int upperboud, int num_of_tials);
void intgerRangeValidation(int& variable, int lower_bound, int upperboud, std::string& message);
void intgerRangeValidation(int& variable, int lower_bound, int upperboud, std::string&& message);
void intgerRangeValidation(int& variable, int lower_bound, int upperboud);
