#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class PinState : public WindowState {

public:
    PinState(MainWindow* context): WindowState(context) {}


private:
    const QString do_screenName() override {
        return "Enter the pin code";
    }

    void do_clearCurrentPage() override {
        getUi()->pinField->clear();
        getUi()->pinField->setFocus();
        getUi()->wrongPINLabel->setText("");
    }

    void do_enterNum(char num) override {
        QString prev = getUi()->pinField->text();
        if (prev.length()==8) return;
        getUi()->pinField->setText(prev+num);
    }

    void do_handleButtonCorrect() override {
        QString prev = getUi()->pinField->text();
        QString newText = prev.length() == 0 ? "" : prev.chopped(1);
        getUi()->pinField->setText(newText);
    }

    void do_handleButtonDelete() override {
        getUi()->pinField->setText("");
    }

    void do_handleButtonEnter() override {
        bool valid = emit context->validateLogin(getUi()->pinField->text().toStdString());

        if (valid)
            context->goToPage(Menu);
        else
            context->wrongPin(0); //TODO add tries left

    }

    void do_handleButtonR4() override {
        context->endSession();
    }

    void do_handleButtonL4() override {
        handleButtonEnter();
    }
};
