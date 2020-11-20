#ifndef ADMINSTATE_H
#define ADMINSTATE_H
#include "WindowState.h"
#include "mainwindow.h"

class AdminState : public WindowState {

    const QString screenName() override {
        return "Admin";
    }

    void clearCurrentPage() override {
        getUi()->spinBox->setValue(0);
        getUi()->spinBox_1->setValue(0);
        getUi()->spinBox_2->setValue(0);
        getUi()->spinBox_3->setValue(0);
        getUi()->spinBox_4->setValue(0);
    }

    void handleButtonL4() override {
        context->goToPage(Welcome);
    }

     void handleButtonL3() override {
// save money
     }

};

#endif // ADMINSTATE_H
