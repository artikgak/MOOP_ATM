#include "testfront.h"


Test_Front::Test_Front(MainWindow& mw1, ATM& atm1): mw(mw1), atm(atm1)
{
}


void Test_Front::testInputPIN()
{
    mw.goToPage(EnterPIN);
    mw.ui->button0->click();
    mw.ui->button1->click();
    mw.ui->button2->click();
    mw.ui->button3->click();
    mw.ui->button4->click();
    mw.ui->button5->click();
    mw.ui->button6->click();
    mw.ui->button7->click();
    mw.ui->button8->click();
    mw.ui->button9->click();
    QVERIFY(mw.ui->pinField->text()=="********");
}
