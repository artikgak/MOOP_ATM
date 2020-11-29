#include "testfront.h"
#include "Utils.h"

Test_Front::Test_Front(): atm(new ATM()), mw(new MainWindow(*atm))
{

}

void Test_Front::initTestCase() //will be called before the first test function is executed.
{
    atm->card = new std::string("1234123412341234");
}

void Test_Front::cleanupTestCase() //will be called after the last test function was executed.
{
    delete mw;
    delete atm;
}

void Test_Front::init() //will be called before each test function is executed.
{
    mw->goToPage(EnterPIN);
}

void Test_Front::cleanup() //will be called after every test function.
{
    delete atm->pin;
    atm->pin = nullptr;
}

void Test_Front::testInputPIN()
{
    mw->goToPage(EnterPIN);
    mw->ui->button1->click();
    mw->ui->button2->click();
    mw->ui->button3->click();
    mw->ui->button4->click();
    QVERIFY(mw->ui->pinField->text().length()==4);
    mw->ui->buttonL4->click();
    QVERIFY(*(atm->pin)=="1234");  // is it correct that pin is saved at this point?
    QVERIFY(mw->ui->stackedWidget->currentIndex()==Menu);
}

void Test_Front::testWrongPIN()
{
    mw->goToPage(EnterPIN);
    mw->ui->button1->click();
    mw->ui->button2->click();
    QVERIFY(mw->ui->pinField->text().length()==2);
    mw->ui->buttonL4->click();
    QVERIFY(mw->ui->stackedWidget->currentIndex()==EnterPIN);
    QVERIFY(mw->ui->wrongPINLabel->text()!="");
}
