#ifndef SUCCESSFAILSTATE_H
#define SUCCESSFAILSTATE_H

#include "WindowState.h"
#include "mainwindow.h"

#include "Utils.h"

class SuccessFailState : public WindowState {

private:
    ScreenPage _prevScreen;

public:
    SuccessFailState(const ScreenPage sp): _prevScreen(sp){}
private:
    const QString do_screenName() override {
        return "Query result";
    }

    void do_clearCurrentPage() override {
        getUi()->succFailLab->setText("");
        getUi()->succFailLab->setStyleSheet("");
    }

    void do_handleButtonR4() override {
        context->goToPage(Menu);
    }

    void do_handleButtonL4() override {
            context->goToPage(_prevScreen);
    }

};

#endif // SUCCESSFAILSTATE_H
