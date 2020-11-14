#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <string>
#include <Card.h>

class DataBase
{
private:
    QSqlDatabase _db;

    DataBase(const DataBase&) = delete; // Only one database in a program
    DataBase& operator=(const DataBase&) = delete;

public:
    DataBase(std::string name = "DefaultDB");
    ~DataBase();

    bool isTableExists(const char *);
    bool addCortege(const std::string, const std::string, const double);
    bool deleteCortege(const std::string);
    bool getDataByCardNo(const std::string);
    bool checkPin(const std::string, const std::string);
    double getMoney(const std::string);
    bool addMoney(const std::string, const double);

    bool getAllData();
    bool deleteAllData();
};

#endif // DATABASE_H
