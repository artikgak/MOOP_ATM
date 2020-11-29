#include "DataBase.h"
#include <iostream>

//#ifndef QT_NO_DEBUG
#define IS_TRUE(x) { if (!x) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl << std::flush; else std::cout << "ok\n"; }
//#endif

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
                                     "id INTEGER,"
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

bool DataBase::addCortegeCard(const std::string cardNo, const std::string pin, const double balance)
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
        qDebug() << "error: adding cortege to the card table";
        return false; // cortege wasn't added
    }
    return true; // cortege was added
}

bool DataBase::addCortegeAdmin(const std::string password)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO admin_passwrds ("
                "password)"
                "VALUES (?);");

    qry.addBindValue(QString::fromStdString(password));

    if (!qry.exec()) {
        qDebug() << "error: adding cortege to the admin_passwrds table";
        return false; // cortege wasn't added
    }
    return true; // cortege was added
}

bool DataBase::addCortegeCharity(const std::string name, const std::string description)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO charity ("
                "name,"
                "description)"
                "VALUES (?,?);");

    qry.addBindValue(QString::fromStdString(name));
    qry.addBindValue(QString::fromStdString(description));

    if (!qry.exec()) {
        qDebug() << "error: adding cortege to the charity table";
        return false; // cortege wasn't added
    }
    return true; // cortege was added
}

bool DataBase::deleteCortegeCard(const std::string cardNumber)
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
    std::string query("UPDATE card SET balance = '" + QString("%6").arg(balance + amount).toStdString() + "' WHERE cardNo='" + cardNumber + "';");
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

std::vector<Charity> getCharities(int page, int info_per_page)
{
    QSqlQuery qry;
    std::string query("SELECT * FROM charity;");
    qry.prepare(query.c_str());

    std::vector<Charity> result;

    if (!qry.exec() || page < 0 || info_per_page < 1) {
        qDebug() << "error: getting data from the charity table";
        return result; // there is some error while executing query
    }

    int ipp = 0;
    int pg = 0;
    while (qry.next() && ipp < info_per_page) {
        if (pg < page * info_per_page) {
            ++pg;
        }
        else {
            uint id = qry.value(0).toInt();
            QString name = qry.value(1).toString();
            QString descr = qry.value(2).toString();
            Charity charity{id, name.toStdString(), descr.toStdString()};
            result.push_back(charity);
            ++ipp;
        }
    }
    return result;
}

bool DataBase::outputAllDataCard()
{
    QSqlQuery qry;
    std::string query("SELECT * FROM card;");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: getting data from the card table";
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

bool DataBase::outputAllDataAdmin()
{
    QSqlQuery qry;
    std::string query("SELECT * FROM admin_passwrds;");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: getting data from the admin_passwrds table";
        return false; // there is some error while executing query
    }

    bool check = false;
    while (qry.next()) {
        QString password = qry.value(0).toString();
        qDebug() << password;
        check = true;
    }
    if (!check) {
        return false; // There is no data
    }
    return true; // There is data
}

bool DataBase::outputAllDataCharity()
{
    QSqlQuery qry;
    std::string query("SELECT * FROM charity;");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: getting data from the charity table";
        return false; // there is some error while executing query
    }

    bool check = false;
    while (qry.next()) {
        int id = qry.value(0).toInt();
        QString name = qry.value(1).toString();
        QString descr = qry.value(2).toString();
        qDebug() << id << name << descr;
        check = true;
    }
    if (!check) {
        return false; // There is no data
    }
    return true; // There is data
}

bool DataBase::deleteAllData()
{
    {
        QSqlQuery qry;
        std::string query("DELETE FROM card;");
        qry.prepare(query.c_str());

        if (!qry.exec()) {
            qDebug() << "error: deleting data from the card table";
            return false; // there is some error while executing query
        }
    }

    {
        QSqlQuery qry;
        std::string query("DELETE FROM charity;");
        qry.prepare(query.c_str());

        if (!qry.exec()) {
            qDebug() << "error: deleting data from the charity table";
            return false; // there is some error while executing query
        }
    }

    {
        QSqlQuery qry;
        std::string query("DELETE FROM admin_passwrds;");
        qry.prepare(query.c_str());

        if (!qry.exec()) {
            qDebug() << "error: deleting data from the admin_passwrds table";
            return false; // there is some error while executing query
        }
    }

    return true;
}

void fullDB(DataBase& db)
{
    /* Adding to card table */
    db.addCortegeCard("8888888888888888", "8888", 88888888);
    db.addCortegeCard("5555555555555555", "5555", 55.55);
    db.addCortegeCard("7777777777777777", "7007", 7007);
    db.addCortegeCard("6666666666666666", "6116", 666.666);

    /* Adding to admin table */
    db.addCortegeAdmin("cisco");
    db.addCortegeAdmin("password");
    db.addCortegeAdmin("admin");

    /* Adding to charity table */
    db.addCortegeCharity("charity1", "description for charity 1");
    db.addCortegeCharity("charity2", "description for charity 2");
    db.addCortegeCharity("charity3", "description for charity 3");
}
