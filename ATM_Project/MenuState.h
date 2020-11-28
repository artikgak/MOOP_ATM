#pragma once

#include "WindowState.h"
#include "mainwindow.h"
#include <QMessageBox>

class MenuState : public WindowState {
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream

    const QString screenName() override {
        return "Меню вибору";
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
private:
    const QString do_screenName() override {
        return "Menu";
>>>>>>> Stashed changes
    }

    void do_clearCurrentPage() override {
        return;
    }

<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    void handleButtonL1() override {
        emit context->getBalance();
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    void do_handleButtonL1() override {
        std::string money = emit context->getBalance();
        context->displayBalance(money);
>>>>>>> Stashed changes
    }

    void do_handleButtonL2() override {
        context->goToPage(GetCash);
    }

    void do_handleButtonL3() override{
        context->goToPage(TransactionData);
    }

    void do_handleButtonL4() override{
    QMessageBox msgBox;
    msgBox.setText("Has not been implemented yed.");
    msgBox.exec();
    }

    void handleButtonR1() override{
    QMessageBox msgBox;
    msgBox.setText("Has not been implemented yed.");
    msgBox.exec();
    }

    void do_handleButtonR2() override{
    QMessageBox msgBox;
    msgBox.setText("Has not been implemented yed.");
    msgBox.exec();
    }

    void do_handleButtonR4() override {
        context->endSession();
    }

};
