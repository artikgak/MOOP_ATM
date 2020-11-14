#ifndef TEST_FRONT_H
#define TEST_FRONT_H

#include <QObject>
#include <QtTest/QtTest>
#include "mainwindow.h"
#include "ATM.h"
#include "ui_mainwindow.h"

class Test_Front : public QObject
{
    Q_OBJECT
public:
    explicit Test_Front(MainWindow& mw, ATM& atm);

private slots:
    void testInputPIN();

private:
MainWindow& mw;
ATM& atm;
};

#endif // TEST_FRONT_H
