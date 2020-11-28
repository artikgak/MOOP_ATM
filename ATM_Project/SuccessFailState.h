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
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream

    const QString screenName() override {
        return "Результат запиту";
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
private:
    const QString do_screenName() override {
        return "Query result";
>>>>>>> Stashed changes
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
