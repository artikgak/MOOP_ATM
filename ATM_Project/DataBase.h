#pragma once

#include <QtSql>
#include <string>
#include "Charity.h"

class DataBase
{
private:
    QSqlDatabase _db;
    const uint64_t credit_limit = 2000;

    /* Only one database in a program */
    DataBase(const DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;

public:
    DataBase(std::string name = "DefaultDB");
    ~DataBase();

    /*Database management queries*/
    void createTables();
    bool isTableExists(const char *);

    /*Money-connected queries*/
    bool cardExists(const std::string);
    bool addCortegeCard(const std::string, const std::string, const double);
    bool deleteCortegeCard(const std::string);
    bool checkTries(const std::string);
    int getTries(const std::string);
    bool checkPin(const std::string, const std::string);
    double getMoney(const std::string);
    bool addMoney(const std::string, const double);
    bool outputAllDataCard();

    /*Admin-connected queries*/
    bool adminExists(const std::string);
    bool addCortegeAdmin(const std::string);
    bool outputAllDataAdmin();

    /*Charity-connected queries*/
    bool charityExists(const std::string);
    bool addCortegeCharity(const std::string, const std::string);
    std::vector<Charity> getCharities(int, int);
    bool outputAllDataCharity();

    bool deleteAllData();

    /* unit tests */
    void testDB();
    void cardExistsTest();
    void addMoneyTest();
    void adminExistsTest();
};

/* Put some data into database */
void fullDB(DataBase&);
