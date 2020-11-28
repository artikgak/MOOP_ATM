#ifndef ADMINSTATE_H
#define ADMINSTATE_H
#include "WindowState.h"
#include "mainwindow.h"

class AdminState : public WindowState {
private:
    const QString do_screenName() override {
        return "Admin";
    }

    void do_clearCurrentPage() override {
        getUi()->spinBox->setValue(0);
        getUi()->spinBox_1->setValue(0);
        getUi()->spinBox_2->setValue(0);
        getUi()->spinBox_3->setValue(0);
        getUi()->spinBox_4->setValue(0);
    }

    void do_handleButtonL4() override {
        context->goToPage(Welcome);
    }

     void do_handleButtonL3() override {
        context->saveBankNotes();
     }

};

#endif // ADMINSTATE_H
