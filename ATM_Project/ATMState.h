#pragma once
#include "Utils.h"

class ATM;

class ATMState {

protected:
    ATM *context_;

public:
    virtual ~ATMState() {}

    void set_context(ATM *context) {
      this->context_ = context;
    }

    virtual void pushPinButton(const PinButton pb) = 0;
    virtual void pushScreenButton(const ScreenButton sb) = 0;
};
