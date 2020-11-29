#pragma once

#include "Utils.h"
#include <ui_mainwindow.h>
#include <QSound>

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

    void plSo(){QSound::play(":sounds/button.wav");}
public:
    virtual ~WindowState() {}

    WindowState(MainWindow *context) {
        this->context = context;
    }

     void clearCurrentPage() {do_clearCurrentPage();}
     const QString screenName() {return     do_screenName();}

     void enterNum(char c) {plSo();do_enterNum(c);}

     void handleButtonMinus() {plSo();do_handleButtonMinus();}
     void handleButtonPlus() {plSo();do_handleButtonPlus();}

     void handleButtonL1() {plSo();do_handleButtonL1();}
     void handleButtonL2() {plSo();do_handleButtonL2();}
     void handleButtonL3() {plSo();do_handleButtonL3();}
     void handleButtonL4() {plSo();do_handleButtonL4();}

     void handleButtonR1() {plSo();do_handleButtonR1();}
     void handleButtonR2() {plSo();do_handleButtonR2();}
     void handleButtonR3() {plSo();do_handleButtonR3();}
     void handleButtonR4() {plSo();do_handleButtonR4();}

     void handleButtonDelete()  {plSo();do_handleButtonDelete();}
     void handleButtonEnter()   {plSo();do_handleButtonEnter();}
     void handleButtonNothing() {plSo();do_handleButtonNothing();}
     void handleButtonCorrect() {plSo();do_handleButtonCorrect();}
};
