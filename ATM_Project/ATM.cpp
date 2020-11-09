#include "ATM.h"

ATM::ATM():
    card(nullptr),
    state(nullptr)
    {
    

    

}

ATM* ATM::getInstance() {
    if (singletonInstance == nullptr)
        singletonInstance = new ATM();
    return singletonInstance;
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