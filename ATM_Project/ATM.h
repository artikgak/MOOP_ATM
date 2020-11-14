#pragma once

#include "Card.h"
#include "Utils.h"
#include "DataBase.h"
#include "QObject"

class MainWindow;

class ATM : public QObject
{
    Q_OBJECT
private:
    /* Class variables */
    MainWindow* mainW;

    DataBase& db;
    Card* card;
    ATMState state;


    ATM& operator=(ATM&) = delete;
    ATM(ATM&) = delete;

public:
    ATM();
    ~ATM();

    bool insertCard(Card);

    void pushButton(const Button button);

public slots:
    void validateCard(std::string cardNum);
    void validatePin(std::string pin);
    void ejectCard();

signals:
    void errorMsg(const QString& errorMsg, ScreenPage whereToGo);
    void goToPage(const ScreenPage);
};

