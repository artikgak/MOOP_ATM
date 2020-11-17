#include "DataBase.h"
#include <filesystem>
#include <iostream>

DataBase::DataBase(std::string name)
{
    //std::cout << QCoreApplication::applicationDirPath().toStdString() << '\n';
    //std::string path = "/Users/akreidun/Desktop/MOOP_ATM/ATM_Project/";
    std::string path = ":/ATM_Project/";
    std::string extention(".sqlite");
    std::string full_name = path + name + extention;

    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(full_name.c_str());

    if (!_db.open()) {
        qDebug() << "error: problem opening database";
    } else {
        if (!isTableExists("card")) {
            QString create_table_query = "CREATE TABLE card ("
                                         "cardNo VARCHAR(16) NOT NULL,"
                                         "pin VARCHAR(4) NOT NULL,"
                                         "balance double NOT NULL,"
                                         "tries int NOT NULL,"
                                         "PRIMARY KEY (cardNo));";
            QSqlQuery create_table_qry;
            if (!create_table_qry.exec(create_table_query)) {
                qDebug() << "error: creating table";
            }
        }
        this->addCortege("1234123412341240", "1234", 0);
        this->addCortege("1234123412341241", "4321", 11231.12321);
    }
}

DataBase::~DataBase()
{
    _db.close();
}

bool DataBase::isTableExists(const char *tablename)
{
    if (!_db.tables().contains(tablename)) {
        return false;
    }
    return true;
}

bool DataBase::addCortege(const std::string cardNo, const std::string pin, const double balance)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO card ("
                "cardNo,"
                "pin,"
                "balance,"
                "tries)"
                "VALUES (?,?,?,?);");

    qry.addBindValue(QString::fromStdString(cardNo));
    qry.addBindValue(QString::fromStdString(pin));
    qry.addBindValue(balance);
    qry.addBindValue(3);

    if (!qry.exec()) {
        qDebug() << "error: adding cortege to a database";
        return false; // cortege wasn't added
    }
    return true; // cortege was added
}

bool DataBase::deleteCortege(const std::string cardNumber)
{
    QSqlQuery qry;
    std::string query("DELETE FROM card WHERE cardNo='" + cardNumber + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: deleting data from a database";
        return false; // cortege was deleted
    }
    return true; // cortege wasn't deleted
}

bool DataBase::cardExists(const std::string cardNumber)
{
    QSqlQuery qry;
    std::string query("SELECT * FROM card WHERE cardNo='" + cardNumber + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: getting data from a database";
        return false; // there is some error while executing query
    }

    return qry.next();
}

bool DataBase::checkTries(const std::string cardNumber)
{
    if (!cardExists(cardNumber)) {
        qDebug() << "There is no card with this number";
        return false;
    }
    QSqlQuery qry;
    std::string query("SELECT * FROM card WHERE cardNo='" + cardNumber + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: getting data from a database";
        return false; // there is some error while executing query
    }
    if (qry.next()) {
        int tries = qry.value(3).toInt();
        if (tries < 1)
            return false;
    }
    return true;
}

bool DataBase::checkPin(const std::string cardNumber, const std::string pin_code)
{
    if (!cardExists(cardNumber)) {
        qDebug() << "There is no card with this number";
        return false;
    }
    if (!checkTries(cardNumber)) {
        qDebug() << "There is no tries left! Please contact your administrator!";
        return false;
    }
    QSqlQuery qry;
    std::string query("SELECT * FROM card WHERE cardNo='" + cardNumber + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: getting data from a database";
        return false; // there is some error while executing query
    }
    int tries = -1;
    if (qry.next()) {
        std::string pin = qry.value(1).toString().toStdString();
        tries = qry.value(3).toInt();
        if (pin != pin_code) {
            --tries;
            if (tries <= 1)
                tries = 1;
            QSqlQuery qry1;
            std::string query1("UPDATE card SET tries = tries - 1 WHERE cardNo='" + cardNumber + "';");
            qry1.prepare(query1.c_str());
            if (!qry1.exec()) {
                qDebug() << "error: changing amount of tries to enter pin";
                return false;
            }
            return false; // pin code is wrong
        }
    }
    else {
        return false; // There is no data
    }
    QSqlQuery qry1;
    std::string query1("UPDATE card SET tries = 3 WHERE cardNo='" + cardNumber + "';");
    qry1.prepare(query1.c_str());
    if (!qry1.exec()) {
        qDebug() << "error: changing amount of tries to enter pin";
        return false;
    }
    return true; // There is data and it's ok
}

double DataBase::getMoney(const std::string cardNumber)
{
    if (!cardExists(cardNumber)) {
        qDebug() << "There is no card with this number";
        return false; // getting money was not performed
    }
    QSqlQuery qry;
    std::string query("SELECT * FROM card WHERE cardNo='" + cardNumber + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: getting money from a database by provided cardNumber";
        return false; // there is some error while executing query
    }
    if (qry.next()) {
        double balance = qry.value(2).toDouble();
        return balance; // there is data
    }
    return -1; // There is no data
}

bool DataBase::addMoney(const std::string cardNumber, const double amount)
{
    if (!cardExists(cardNumber)) {
        qDebug() << "There is no card with this number";
        return false; // adding was not performed
    }
    double balance = getMoney(cardNumber);
    QSqlQuery qry;
    std::string query("UPDATE card SET balance = '" + QString("%1").arg(balance + amount).toStdString() + "' WHERE cardNo='" + cardNumber + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: adding money";
        return false; // there is some error while executing query
    }
    return true; // Money added
}

bool DataBase::getAllData()
{
    QSqlQuery qry;
    std::string query("SELECT * FROM card;");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: getting data from a database";
        return false; // there is some error while executing query
    }

    bool check = false;
    while (qry.next()) {

    // Here we need to save all Card objects according to this data

        QString cardNo = qry.value(0).toString();
        QString pin = qry.value(1).toString();
        double balance = qry.value(2).toDouble();

    // ---

        // qDebug() << cardNo << pin << balance;
        check = true;
    }
    if (!check) {
        return false; // There is no data
    }
    return true; // There is data
}

bool DataBase::deleteAllData()
{
    QSqlQuery qry;
    std::string query("DELETE FROM card;");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: deleting data from a database";
        return false; // there is some error while executing query
    }
    return true;
}
