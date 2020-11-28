#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class IdleState : public WindowState {

    const QString screenName() override {
        return "Welcome!";
    }

    void clearCurrentPage() override {
        getUi()->wrongCardNumLabel->setText("");
    }
};
