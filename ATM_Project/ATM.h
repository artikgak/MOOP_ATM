#pragma once

#include "Card.h"
#include "ATMState.h"

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
};

