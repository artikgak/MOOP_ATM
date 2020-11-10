#pragma once

#include "Card.h"
#include "ATMState.h"
#include "Utils.h"

class MainWindow;

class ATM
{
private:
    ATM& operator=(ATM&) = delete;
    ATM(ATM&) = delete;
    MainWindow& mainW;
    /* State of ATM*/
    ATMState* state;
    /* Class variables */ 
    Card* card;


public:
    ATM(MainWindow& subject);
    ~ATM();
    /* State transition */
    void transitionTo(ATMState *state);


    bool insertCard(Card);

    friend class ATMState; // TODO: see if needed 

    void pushScreenButton(const ScreenButton button) {
        state->pushScreenButton(button);
    }

    void pushPinButton(const PinButton button) {
        state->pushPinButton(button);
    }

};

