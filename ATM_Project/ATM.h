#pragma once

#include "Card.h"
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
    Card* card;
    std::string* pin;
    ATMState state;

    ATM& operator=(ATM&) = delete;
    ATM(ATM&) = delete;

//    template<class voidFunc>
//    void validatePinAndEmit(const std::string& pin, voidFunc toEmit);

public:
    friend Test_Front;
    ATM();
    ~ATM();

// Signals received from UI
public slots:
    WithdrawResponse withdrawMoney(const uint sum);
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
};

