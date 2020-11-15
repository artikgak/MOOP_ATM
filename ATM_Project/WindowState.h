#pragma once

#include <ui_mainwindow.h>

class MainWindow;

class WindowState {

protected:
    MainWindow *context;
    Ui::MainWindow* getUi();

public:
    virtual ~WindowState() {}

    void set_context(MainWindow *context) {
        this->context = context;
    }

    virtual void clearCurrentPage() = 0;
    virtual const QString screenName() = 0;



    virtual void enterNum(char) {}

    virtual void handleButtonMinus() {}
    virtual void handleButtonPlus() {}

    virtual void handleButtonL1() {}
    virtual void handleButtonL2() {}
    virtual void handleButtonL3() {}
    virtual void handleButtonL4() {}

    virtual void handleButtonR1() {}
    virtual void handleButtonR2() {}
    virtual void handleButtonR3() {}
    virtual void handleButtonR4() {}

    virtual void handleButtonDelete() {}
    virtual void handleButtonEnter() {}
    virtual void handleButtonNothing() {}
    virtual void handleButtonCorrect() {}
};
