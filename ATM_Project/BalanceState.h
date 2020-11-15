#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class BalanceState : public WindowState {

    void clearCurrentPage() override {
        getUi()->cashBalanceLabel->clear();
    }

    void enterNum(char) override {
        return;
    }
};
