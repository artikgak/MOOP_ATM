#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class IdleState : public WindowState {
public:
    IdleState(MainWindow* context): WindowState(context) {}

private:
    const QString do_screenName() override {
        return "Welcome!";
    }

    void do_clearCurrentPage() override {
        getUi()->wrongCardNumLabel->setText("");
    }
};
