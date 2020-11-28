#include "mainwindow.h"
#include "ATM.h"
#include "testfront.h"

#include <QApplication>
#include <QtTest/QtTest>

#define QT_NO_DEGUB

int main(int argc, char *argv[])
{
    ATM atm;
    QApplication a(argc, argv);
    MainWindow w(&atm);
    w.show();
#ifndef QT_NO_DEBUG
  //  QTest::qExec(new Test_Front());
#endif
    return a.exec();
}
