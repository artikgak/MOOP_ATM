#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <string>

class DataBase
{
private:
    QSqlDatabase _db;

    DataBase(const DataBase&) = delete; /* Only one database in a program */
    DataBase& operator=(const DataBase&) = delete;

public:
    DataBase(std::string name = "DefaultDB");
    ~DataBase();

    void createTables();
    bool isTableExists(const char *);
    bool addCortege(const std::string, const std::string, const double);
    bool deleteCortege(const std::string);
    bool cardExists(const std::string);
    bool checkTries(const std::string);
    bool checkPin(const std::string, const std::string);
    double getMoney(const std::string);
    bool addMoney(const std::string, const double);

    bool getAllData();
    bool deleteAllData();

    /* unit tests */
    void cardExistsTest();
    void addMoneyTest();
};

/* Put some data into database */
void fullDB(DataBase&);

#endif /* DATABASE_H */
