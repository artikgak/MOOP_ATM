#include "DataBase.h"

DataBase::DataBase(std::string name)
{
    std::string path("/Users/akreidun/Desktop/");
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
                                         "PRIMARY KEY (cardNo));";
            QSqlQuery create_table_qry;

            if (!create_table_qry.exec(create_table_query)) {
                qDebug() << "error: creating table";
            }
        }
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

bool DataBase::addCortege(const QString cardNo, const QString pin, const double balance)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO card ("
                "cardNo,"
                "pin,"
                "balance)"
                "VALUES (?,?,?);");

    qry.addBindValue(cardNo);
    qry.addBindValue(pin);
    qry.addBindValue(balance);

    if (!qry.exec()) {
        qDebug() << "error: adding cortege to a database";
        return false; // cortege wasn't added
    }
    return true; // cortege was added
}

bool DataBase::deleteCortege(const QString cardNumber)
{
    QSqlQuery qry;
    std::string query("DELETE FROM card WHERE cardNo='" + cardNumber.toStdString() + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: deleting data from a database";
        return false; // cortege was deleted
    }
    return true; // cortege wasn't deleted
}

bool DataBase::getDataByCardNo(const QString cardNumber)
{
    QSqlQuery qry;
    std::string query("SELECT * FROM card WHERE cardNo='" + cardNumber.toStdString() + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: getting data from a database";
        return false; // there is some error while executing query
    }

    if (qry.next()) {

    // Here we need change Card object to save this data

        QString cardNo = qry.value(0).toString();
        QString pin = qry.value(1).toString();
        double balance = qry.value(2).toDouble();

    // ---

        // qDebug() << cardNo << pin << balance;
    }
    else {
        return false; // There is no data
    }
    return true; // There is data
}

bool DataBase::checkPin(const QString cardNumber, const QString pin_code)
{
    QSqlQuery qry;
    std::string query("SELECT * FROM card WHERE cardNo='" + cardNumber.toStdString() + "';");
    qry.prepare(query.c_str());

    if (!qry.exec()) {
        qDebug() << "error: getting data from a database";
        return false; // there is some error while executing query
    }

    if (qry.next()) {
        QString pin = qry.value(1).toString();

        if (pin != pin_code) {
            return false; // pin code is wrong
        }
    }
    else {
        return false; // There is no data
    }
    return true; // There is data and it's ok
}

double DataBase::getMoney(const QString cardNumber)
{
    QSqlQuery qry;
    std::string query("SELECT * FROM card WHERE cardNo='" + cardNumber.toStdString() + "';");
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

bool DataBase::addMoney(const QString cardNumber, const double amount)
{
    if (!getDataByCardNo(cardNumber)) {
        qDebug() << "There is no card with this number";
        return false; // adding was not performed
    }
    double balance = getMoney(cardNumber);
    QSqlQuery qry;
    std::string query("UPDATE card SET balance = '" + QString("%1").arg(balance + amount).toStdString() + "' WHERE cardNo='" + cardNumber.toStdString() + "';");
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
