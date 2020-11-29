#include "DataBase.h"
//#include <filesystem>
#include <iostream>

#ifndef QT_NO_DEBUG
#define IS_TRUE(x) { if (!x) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl << std::flush; else std::cout << "ok\n"; }
#endif

DataBase::DataBase(std::string name)
{
    std::string path = "E:/Workspace/Programming/MOOP_ATM/ATM_Project/";
    //std::string path = "../ATM_Project/";
    std::string extention(".sqlite");
    std::string full_name = path + name + extention;

    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(full_name.c_str());

    if (!_db.open()) {
        qDebug() << "error: problem opening database";
    } else {
        createTables();
    }

#ifndef QT_NO_DEBUG
    std::cout << "********* Start testing of cardExist *********" << std::flush;
    cardExistsTest();
    std::cout << "********* Finished testing of cardExist *********" << std::flush;
    std::cout << "********* Start testing of addMoneyTest *********" << std::flush;
    addMoneyTest();
    std::cout << "********* Finished testing of addMoneyTest *********" << std::flush;
#endif
}

DataBase::~DataBase()
{
    _db.close();
}

void DataBase::createTables()
{
    if (!isTableExists("card")) {
        QString create_table_query = "CREATE TABLE card ("
                                     "cardNo VARCHAR(16) NOT NULL,"
                                     "pin VARCHAR(4) NOT NULL,"
                                     "balance double NOT NULL,"
                                     "tries int NOT NULL,"
                                     "PRIMARY KEY (cardNo));";
        QSqlQuery create_table_qry;
        if (!create_table_qry.exec(create_table_query)) {
            qDebug() << "error: creating table 'card'";
        }
    }
    if(!isTableExists("admin_passwrds")) {
        QString create_table_query = "CREATE TABLE admin_passwrds ("
                                     "password VARCHAR(8) NOT NULL,"
                                     "PRIMARY KEY (password));";
        QSqlQuery create_table_qry;
        if (!create_table_qry.exec(create_table_query)) {
            qDebug() << "error: creating table 'admin_passwrds'";
        }
    }
    if(!isTableExists("charity")) {
        QString create_table_query = "CREATE TABLE charity ("
                                     "id UNSIGNED INT NOT NULL,"
                                     "name VARCHAR(10) NOT NULL,"
                                     "description VARCHAR(150),"
                                     "PRIMARY KEY (id));";
        QSqlQuery create_table_qry;
        if (!create_table_qry.exec(create_table_query)) {
            qDebug() << "error: creating table 'charity'";
        }
    }
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
    if (!cardExists(cardNumber)) {
        qDebug() << "There is no card with this number";
        return false;
    }
    QSqlQuery qry;
    std::string query("DELETE FROM card WHERE cardNo='" + cardNumber + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: deleting data from a database";
        return false; // cortege wasn't deleted
    }
    return true; // cortege was deleted
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

void DataBase::cardExistsTest()
{
    IS_TRUE(cardExists("1234123412341234"));
    IS_TRUE(!cardExists("12341234123412344"));
    IS_TRUE(cardExists("1234123412341235"));
    IS_TRUE(cardExists("1234123412341238"));
    IS_TRUE(cardExists("1234123412341239"));
    IS_TRUE(cardExists("1234123412341240"));
    IS_TRUE(cardExists("1234123412341241"));
    IS_TRUE(!cardExists("1234123412341250"));
    IS_TRUE(!cardExists("123123ed123"));
    IS_TRUE(!cardExists("12321asfasf"));
    IS_TRUE(!cardExists(""));
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
    std::cout << "Entered\n";
    if (!cardExists(cardNumber)) {
        qDebug() << "There is no card with this number";
        return false; // adding was not performed
    }
    if (amount < 0 && getMoney(cardNumber) < -amount) {
        qDebug() << "There is not enough money on this card!";
        return false; // adding was not performed
    }
    double balance = getMoney(cardNumber);
    QSqlQuery qry;
    std::string query("UPDATE card SET balance = '" + QString("%3").arg(balance + amount).toStdString() + "' WHERE cardNo='" + cardNumber + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: adding money";
        return false; // there is some error while executing query
    }
    return true; // Money added
}

void DataBase::addMoneyTest()
{
    double eps = 0.000001;
    IS_TRUE(!addMoney("12321", 1231));
    IS_TRUE(!addMoney("12321", -1231));
    double before = getMoney("1234123412341234");
    IS_TRUE(addMoney("1234123412341234", 1231));
    double after = getMoney("1234123412341234");
    IS_TRUE((abs(after - (before + 1231)) < eps));
    IS_TRUE(addMoney("1234123412341234", -1231));
    after = getMoney("1234123412341234");
    IS_TRUE((abs(after - before) < eps));
    IS_TRUE(!addMoney("1234123412341234", -1000000));
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
        QString cardNo = qry.value(0).toString();
        QString pin = qry.value(1).toString();
        double balance = qry.value(2).toDouble();
        qDebug() << cardNo << pin << balance;
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

void fullDB(DataBase& db)
{
    db.addCortege("8888888888888888", "8888", 88888888);
    db.addCortege("5555555555555555", "5555", 55.55);
    db.addCortege("7777777777777777", "7007", 7007);
    db.addCortege("6666666666666666", "6116", 666.666);
}
