#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class BalanceState : public WindowState {

    const QString screenName() override {
        return "Ваш баланс";
    }

    void clearCurrentPage() override {
        getUi()->cashBalanceLabel->clear();
    }

    void enterNum(char) override {
        return;
    }
};
