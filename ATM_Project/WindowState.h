#pragma once

#include "Utils.h"
#include <ui_mainwindow.h>

class MainWindow;

class WindowState {

protected:
    MainWindow *context;
    Ui::MainWindow* getUi();

private:
    virtual void do_clearCurrentPage() = 0;
    virtual const QString do_screenName() = 0;

    virtual void do_enterNum(char) {}

    virtual void do_handleButtonMinus() {}
    virtual void do_handleButtonPlus() {}

    virtual void do_handleButtonL1() {}
    virtual void do_handleButtonL2() {}
    virtual void do_handleButtonL3() {}
    virtual void do_handleButtonL4() {}

    virtual void do_handleButtonR1() {}
    virtual void do_handleButtonR2() {}
    virtual void do_handleButtonR3() {}
    virtual void do_handleButtonR4() {}

    virtual void do_handleButtonDelete() {}
    virtual void do_handleButtonEnter() {}
    virtual void do_handleButtonNothing() {}
    virtual void do_handleButtonCorrect() {}

public:
    virtual ~WindowState() {}

    void set_context(MainWindow *context) {
        this->context = context;
    }

    virtual void clearCurrentPage() { do_clearCurrentPage();}
    virtual const QString screenName(){ do_screenName();}

    virtual void enterNum(char c) {do_enterNum(c);}

    virtual void handleButtonMinus() {do_handleButtonMinus(); }
    virtual void handleButtonPlus() {do_handleButtonPlus();}

    virtual void handleButtonL1() {do_handleButtonL1();}
    virtual void handleButtonL2() {do_handleButtonL2();}
    virtual void handleButtonL3() {do_handleButtonL3();}
    virtual void handleButtonL4() {do_handleButtonL4();}

    virtual void handleButtonR1() {do_handleButtonR1();}
    virtual void handleButtonR2() {do_handleButtonR2();}
    virtual void handleButtonR3() {do_handleButtonR3();}
    virtual void handleButtonR4() {do_handleButtonR4();}

    virtual void handleButtonDelete() {do_handleButtonDelete();}
    virtual void handleButtonEnter() {do_handleButtonEnter();}
    virtual void handleButtonNothing() {do_handleButtonNothing();}
    virtual void handleButtonCorrect() {do_handleButtonCorrect();}
};
