#pragma once

#include "Card.h"
#include "ATMState.h"

enum ScreenButton {
    L1,L2,L3,L4,
    R1,R2,R3,R4
};
enum PinButton {
    B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,
    ENTER, CORRECTION, CANCEL
};

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

