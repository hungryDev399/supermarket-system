#pragma once
#include "pch.h"
struct credentials {
    std::string username, password;
};
extern std::string admin_pass;
extern std::string admin_username;
typedef void (*functio_ptr)();

void getCredentials(credentials& credential);
void startCashierPov();