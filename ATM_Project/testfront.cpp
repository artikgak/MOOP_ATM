#include "testfront.h"


Test_Front::Test_Front(): atm(new ATM()), mw(new MainWindow(atm))
{

}

void Test_Front::enterValidCardNum()
{

}

void Test_Front::initTestCase() //will be called before the first test function is executed.
{
    atm->card = new Card("12345678");
    mw->goToPage(EnterPIN);
}

void Test_Front::cleanupTestCase() //will be called after the last test function was executed.
{
    delete mw;
    delete atm;
}

void Test_Front::init() //will be called before each test function is executed.
{

}

void Test_Front::clean() //will be called after every test function.
{
mw->goToPage(EnterPIN);
}

void Test_Front::testInputPIN()
{
    mw->goToPage(EnterPIN);
    mw->ui->button0->click();
    mw->ui->button1->click();
    mw->ui->button2->click();
    mw->ui->button3->click();
    mw->ui->button4->click();
    mw->ui->button5->click();
    mw->ui->button6->click();
    mw->ui->button7->click();
    mw->ui->button8->click();
    mw->ui->button9->click();
    QVERIFY(mw->ui->pinField->text()=="********");
}
