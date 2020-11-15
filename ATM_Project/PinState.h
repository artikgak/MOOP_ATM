#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class PinState : public WindowState {
private:
    ScreenPage prev;

public:

    PinState(ScreenPage prev) {
        this->prev = prev;
    }

    void clearCurrentPage() override {
        getUi()->pinField->clear();
        getUi()->pinField->setFocus();
        getUi()->wrongPINLabel->clear();
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
        emit context->validateLogin(getUi()->pinField->text().toStdString());
    }

    void handleButtonL4() override {
        emit context->validateLogin(getUi()->pinField->text().toStdString());
    }
};
