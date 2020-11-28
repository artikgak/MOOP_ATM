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

     void clearCurrentPage() {do_clearCurrentPage();}
     const QString screenName() {return     do_screenName();}

     void enterNum(char c) {do_enterNum(c);}

     void handleButtonMinus() {do_handleButtonMinus();}
     void handleButtonPlus() {do_handleButtonPlus();}

     void handleButtonL1() {do_handleButtonL1();}
     void handleButtonL2() {do_handleButtonL2();}
     void handleButtonL3() {do_handleButtonL3();}
     void handleButtonL4() {do_handleButtonL4();}

     void handleButtonR1() {do_handleButtonR1();}
     void handleButtonR2() {do_handleButtonR2();}
     void handleButtonR3() {do_handleButtonR3();}
     void handleButtonR4() {do_handleButtonR4();}

     void handleButtonDelete()  {do_handleButtonDelete();}
     void handleButtonEnter()   {do_handleButtonEnter();}
     void handleButtonNothing() {do_handleButtonNothing();}
     void handleButtonCorrect() {do_handleButtonCorrect();}
};
