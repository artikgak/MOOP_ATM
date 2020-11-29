#pragma once

#include "WindowState.h"
#include "mainwindow.h"
#include <QMessageBox>

class MenuState : public WindowState {
public:

    MenuState(MainWindow* context): WindowState(context) {}

private:
    const QString do_screenName() override {
        return "Menu";
    }

    void do_clearCurrentPage() override {
        return;
    }

    void do_handleButtonL1() override {
        std::string money = emit context->getBalance();
        context->displayBalance(money);
    }

    void do_handleButtonL2() override {
        context->goToPage(GetCash);
    }

    void do_handleButtonL3() override{
        context->goToPage(TransactionData);
    }

    void do_handleButtonL4() override{
    /*QMessageBox msgBox;
    msgBox.setText("Has not been implemented yed.");
    msgBox.exec();*/
        context->goToPage(PhoneData);
    }

    void do_handleButtonR1() override{
        context->goToPage(SelectCharity);
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
