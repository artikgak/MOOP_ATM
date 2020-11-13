#include <QCoreApplication>
#include <QDebug>

#include "DataBase.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "start";

    DataBase my_db ("db");
    my_db.addCortege("1234123412341234", "1234", 0);
    my_db.addCortege("1234123412341235", "4321", 11231.12321);

    my_db.getDataByCardNo("1234123412341234");
    my_db.getDataByCardNo("1234123412341235");
    my_db.getDataByCardNo("1234123412341236");
    my_db.getDataByCardNo("1234123412341235");

    qDebug() << my_db.getDataByCardNo("1234123412341235");
    my_db.deleteCortege("1234123412341235");
    qDebug() << my_db.getDataByCardNo("1234123412341235");

    my_db.addCortege("1234123412341231", "0000", 1000);
    my_db.addCortege("1234123412341239", "1111", 1999.999);

    my_db.getAllData();

    qDebug() << my_db.getMoney("1234123412341231");

    my_db.addMoney("1234123412341231", -10.5);

    qDebug() << my_db.getMoney("1234123412341231");

    my_db.addMoney("1234123412341230", -10.5);

    //my_db.deleteAllData();
    qDebug() << "Data:";
    my_db.getAllData();

    qDebug() << "end";

    qDebug() << my_db.checkPin("1234123412341239", "1111");
    qDebug() << my_db.checkPin("1234123412341239", "1110");

    return a.exec();
}
