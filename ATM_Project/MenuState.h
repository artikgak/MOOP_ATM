#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class MenuState : public WindowState {

    const QString screenName() override {
        return "Меню вибору";
    }

    void clearCurrentPage() override {
        return;
    }

    void handleButtonL1() override {
        emit context->getBalance();
    }

    void handleButtonL2() override {
        context->goToPage(GetCash);
    }

    void handleButtonR4() override {
        context->endSession();
    }

};
