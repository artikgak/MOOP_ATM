#pragma once

#include "Card.h"
#include "ATMState.h"
#include "Utils.h"

class ATM
{
private:
    
    static ATM* singletonInstance;
    ATM();
    /* State of ATM*/
    ATMState* state;

    /* Class variables */ 
    Card* card;

public:


    /* Singleton can't be copied */
    ATM& operator=(ATM&) = delete;
    ATM(ATM&) = delete;
    ~ATM();
    /* State transition */
    void transitionTo(ATMState *state);

    static ATM* getInstance();

    bool insertCard(Card);

    friend class ATMState; // TODO: see if needed 

    void pushScreenButton(const ScreenButton button) {
        state->pushScreenButton(button);
    }

    void pushPinButton(const PinButton button) {
        state->pushPinButton(button);
    }

};

