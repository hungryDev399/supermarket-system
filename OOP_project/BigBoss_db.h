#include <string>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <sqlite3.h>

#include "employee.h"
#include "useful_tools.h"

class BigBoss {
public:
	BigBoss();
	BIGBOSS returnBigBossAsAnObject(int id);
	void updateBigBossObject(BIGBOSS c);
	void printBigBossDataBase();
private:
	void saveBigBossObject();
	sqlite3* db;
	char* errMsg = 0;
	int rc;
};