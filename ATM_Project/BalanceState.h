#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class BalanceState : public WindowState {

    const QString screenName() override {
        return "Ваш баланс";
    }

    void clearCurrentPage() override {
        getUi()->cashBalanceLabel->setText("");
    }

    void handleButtonR4() override{
        context->goToPage(Menu);
    }

    void enterNum(char) override {
        return;
    }
};
