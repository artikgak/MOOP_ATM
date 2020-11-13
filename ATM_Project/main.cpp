#include "mainwindow.h"
#include "ATM.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    ATM atm;
    QApplication a(argc, argv);
    MainWindow w(&atm);
    w.show();
    return a.exec();
}
