#include "ATM.h"
#include "mainwindow.h"

ATM::ATM(MainWindow& subject):
    mainW(subject),
    card(nullptr)
{
    mainW.subscribeATM(this);
}


ATM::~ATM() {
    delete card;
}

bool ATM::insertCard(Card c) {
    if (card == nullptr)
        return false;

    card = &c;
    return true;
}

void ATM::pushButton(const Button button) {
    switch (state) {
    case Idle:
    case S1:
    case S2:
    case S3:
    case Fin:
    case Mntnc:

        break;



//    default:
        ;
    }

}
