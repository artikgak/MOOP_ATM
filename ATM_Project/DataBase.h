#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <string>

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
    bool addCortege(const QString, const QString, const double);
    bool deleteCortege(const QString);
    bool getDataByCardNo(const QString);
    bool checkPin(const QString, const QString);
    double getMoney(const QString);
    bool addMoney(const QString, const double);

    bool getAllData();
    bool deleteAllData();
};

#endif // DATABASE_H
