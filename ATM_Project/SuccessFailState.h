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

    const QString screenName() override {
        return "Результат запиту";
    }

    void clearCurrentPage() override {
        getUi()->succFailLab->setText("");
        getUi()->succFailLab->setStyleSheet("");
    }

    void handleButtonR4() override {
        context->goToPage(Menu);
    }

    void handleButtonL4() override {
            context->goToPage(_prevScreen);
    }

};

#endif // SUCCESSFAILSTATE_H
