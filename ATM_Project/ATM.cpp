#include "ATM.h"
#include "mainwindow.h"

ATM::ATM(MainWindow& subject):
    mainW(subject),
    state(nullptr),
    card(nullptr)
{
    mainW.subscribeATM(this);
}


ATM::~ATM() {
    delete state;
    delete card;
}

bool ATM::insertCard(Card c) {
    if (card == nullptr)
        return false;

    card = &c;
    return true;
}

void ATM::transitionTo(ATMState *newState) {
    if (state != nullptr)
      delete state;
    state = newState;
    state -> set_context(this);
}
