#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class IdleState : public WindowState {

    const QString screenName() override {
        return "Вітаємо!";
    }

    void clearCurrentPage() override {
        getUi()->wrongCardNumLabel->clear();
    }

    void enterNum(char) override {
        return;
    }
};
