#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class IdleState : public WindowState {

    void clearCurrentPage() override {
        getUi()->wrongCardNumLabel->clear();
    }

    void enterNum(char) override {
        return;
    }
};
