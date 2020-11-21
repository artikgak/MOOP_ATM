#pragma once

#include "Utils.h"
#include "DataBase.h"
#include "QObject"

class Test_Front;
class MainWindow;

class ATM : public QObject
{
    Q_OBJECT
private:
    /* Class variables */
    MainWindow* mainW;

    DataBase& db;
    std::string* card;
    std::string* pin;
    ATMState state;

    ATM& operator=(ATM&) = delete;
    ATM(ATM&) = delete;

    QFile file;
//    template<class voidFunc>
//    void validatePinAndEmit(const std::string& pin, voidFunc toEmit);

    void recountBankNotes(const int sum, const int billsSize=5);
public:
static const int bills[5];
void saveBankToFile();
int* bankNotes;

    friend Test_Front;
    ATM();
    ~ATM();

// Signals received from UI
public slots:
    WithdrawResponse withdrawMoney(const uint sum);
    TransferResponse transferMoney(const uint sum, const std::string& cardNum);
    void validateAdmin(const std::string& adminID);
    void validateCard(const std::string& cardNum);
    void validateLogin(const std::string& pin);
    void getBalance();

    void ejectCard();

// Signals sent to UI
signals:
    void errorMsg(const QString& errorMsg, ScreenPage whereToGo);
    void goToPage(const ScreenPage);
    void displayBalance(const std::string&);
    void wrongPin(const uint triesLeft);
    void displayBankNotes(const int*);
};

