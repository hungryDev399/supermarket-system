#pragma once


#include <string>
#include <stdio.h>
#include <sstream>
#include <iomanip> 
#include <iostream>
#include <sqlite3.h>

#include "product_tag.h"


class Product {
public:

    Product();
    PRODUCT returnProductAsAnObjectWithID(int id);
    PRODUCT returnProductAsAnObjectWithCode(int code);
    void saveProductObject(PRODUCT p);
    void deleteProductObject(int id);
    void updateProductObject(PRODUCT& p);
    void printProductDataBase();
    bool checkIfCodeExists(int code);
    void printProductsByName(std::string name);

private:
    sqlite3* db;
    char* errMsg = 0;
    int rc;
};

