#pragma once

#include "WindowState.h"
#include "mainwindow.h"

class IdleState : public WindowState {
<<<<<<< Updated upstream
<<<<<<< Updated upstream

    const QString screenName() override {
        return "Вітаємо!";
=======
=======
>>>>>>> Stashed changes
private:
    const QString do_screenName() override {
        return "Welcome!";
>>>>>>> Stashed changes
    }

    void do_clearCurrentPage() override {
        getUi()->wrongCardNumLabel->setText("");
    }

    void enterNum(char) override {
        return;
    }
};
