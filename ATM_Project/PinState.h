#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class PinState : public WindowState {
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream

    const QString screenName() override {
        return "Введіть пін-код";
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
private:
    const QString do_screenName() override {
        return "Enter the pin code";
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    void handleButtonEnter() override {
        emit context->validateLogin(getUi()->pinField->text().toStdString());
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    void do_handleButtonEnter() override {
        bool valid = emit context->validateLogin(getUi()->pinField->text().toStdString());

        if (valid)
            context->goToPage(Menu);
        else
            context->wrongPin(0); //TODO add tries left

>>>>>>> Stashed changes
    }

    void do_handleButtonR4() override {
        context->endSession();
    }

<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    void handleButtonL4() override {
        emit context->validateLogin(getUi()->pinField->text().toStdString());
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    void do_handleButtonL4() override {
        handleButtonEnter();
>>>>>>> Stashed changes
    }
};
