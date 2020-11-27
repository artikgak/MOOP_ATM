#pragma once

#include "WindowState.h"
#include "mainwindow.h"
#include <QMessageBox>

class MenuState : public WindowState {

    const QString screenName() override {
        return "Меню вибору";
    }

    void clearCurrentPage() override {
        return;
    }

    void handleButtonL1() override {
        std::string money = emit context->getBalance();
        context->displayBalance(money);
    }

    void handleButtonL2() override {
        context->goToPage(GetCash);
    }

    void handleButtonL3() override{
        context->goToPage(TransactionData);
    }

    void handleButtonL4() override{
    QMessageBox msgBox;
    msgBox.setText("Has not been implemented yed.");
    msgBox.exec();
    }

    void handleButtonR1() override{
    QMessageBox msgBox;
    msgBox.setText("Has not been implemented yed.");
    msgBox.exec();
    }

    void handleButtonR2() override{
    QMessageBox msgBox;
    msgBox.setText("Has not been implemented yed.");
    msgBox.exec();
    }

    void handleButtonR4() override {
        context->endSession();
    }

};
