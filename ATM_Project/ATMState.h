#pragma once

class ATM;

class ATMState {

protected:
    ATM *context_;

public:
    virtual ~ATMState() {}

    void set_context(ATM *context) {
      this->context_ = context;
    }

    virtual void act1() = 0;
    virtual void act1() = 0;
};
