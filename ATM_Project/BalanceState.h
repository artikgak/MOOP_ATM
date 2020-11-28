#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class BalanceState : public WindowState {
private:
    const QString do_screenName() override {
        return "Ваш баланс";
    }

    void do_clearCurrentPage() override {
        getUi()->cashBalanceLabel->setText("");
    }

    void do_handleButtonR4() override{
        context->goToPage(Menu);
    }

    void do_enterNum(char) override {
        return;
    }
};
