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
    explicit Test_Front();

private:
    void enterValidCardNum();

private slots:
    void initTestCase(); //will be called before the first test function is executed.
    //void initTestCase_data() will be called to create a global test data table.
    void cleanupTestCase(); //will be called after the last test function was executed.
    void init(); //will be called before each test function is executed.
    void clean(); //will be called after every test function.
    void testInputPIN();

private:
ATM* atm;
MainWindow* mw;
};

#endif // TEST_FRONT_H
