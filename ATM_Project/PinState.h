#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class PinState : public WindowState {

    const QString screenName() override {
        return "Enter the pin code";
    }

    void clearCurrentPage() override {
        getUi()->pinField->clear();
        getUi()->pinField->setFocus();
        getUi()->wrongPINLabel->setText("");
    }

    void enterNum(char num) override {
        QString prev = getUi()->pinField->text();
        if (prev.length()==8) return;
        getUi()->pinField->setText(prev+num);
    }

    void handleButtonCorrect() override {
        QString prev = getUi()->pinField->text();
        QString newText = prev.length() == 0 ? "" : prev.chopped(1);
        getUi()->pinField->setText(newText);
    }

    void handleButtonDelete() override {
        getUi()->pinField->setText("");
    }

    void handleButtonEnter() override {
        bool valid = emit context->validateLogin(getUi()->pinField->text().toStdString());

        if (valid)
            context->goToPage(Menu);
        else
            context->wrongPin(0); //TODO add tries left

    }

    void handleButtonR4() override {
        context->endSession();
    }

    void handleButtonL4() override {
        handleButtonEnter();
    }
};
