#pragma once

class ATM;
enum ScreenButton;
enum PinButton;
class ATMState {

protected:
    ATM *context_;

public:
    virtual ~ATMState() {}

    void set_context(ATM *context) {
      this->context_ = context;
    }

    virtual void pushPinButton(PinButton) = 0;
    virtual void pushScreenButton(ScreenButton) = 0;
};
