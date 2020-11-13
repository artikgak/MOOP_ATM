#pragma once

#include "Card.h"
#include "Utils.h"
#include "QObject"

class MainWindow;

class ATM : public QObject
{
private:
    /* Class variables */
    MainWindow& mainW;

    Card* card;
    ATMState state;


    ATM& operator=(ATM&) = delete;
    ATM(ATM&) = delete;

public:
    ATM(MainWindow& subject);
    ~ATM();

    bool insertCard(Card);

    void pushButton(const Button button);

};

