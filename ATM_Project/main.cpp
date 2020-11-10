#include "mainwindow.h"
#include "ATM.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ATM atm(w);
    w.show();
    return a.exec();
}
