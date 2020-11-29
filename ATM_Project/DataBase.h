#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <string>
#include "Charity.h"

class DataBase
{
private:
    QSqlDatabase _db;
    u_int32_t credit_limit = 2000;

    DataBase(const DataBase&) = delete; /* Only one database in a program */
    DataBase& operator=(const DataBase&) = delete;

public:
    DataBase(std::string name = "DefaultDB");
    ~DataBase();

    void createTables();
    bool isTableExists(const char *);
    bool addCortegeCard(const std::string, const std::string, const double);
    bool addCortegeAdmin(const std::string);
    bool addCortegeCharity(const std::string, const std::string);

    bool deleteCortegeCard(const std::string);
    bool cardExists(const std::string);
    bool adminExists(const std::string);
    bool charityExists(const std::string);
    bool checkTries(const std::string);
    int getTries(const std::string);
    bool checkPin(const std::string, const std::string);
    double getMoney(const std::string);
    bool addMoney(const std::string, const double);

    std::vector<Charity> getCharities(int, int);

    bool outputAllDataCard();
    bool outputAllDataAdmin();
    bool outputAllDataCharity();

    bool deleteAllData();

    /* unit tests */
    void cardExistsTest();
    void adminExistsTest();
    void addMoneyTest();
};

/* Put some data into database */
void fullDB(DataBase&);

#endif /* DATABASE_H */
