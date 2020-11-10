#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Utils.h"
#include <QLabel>

class ATM;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void subscribeATM(ATM*);



    //void showLoader();
    //void hideLoader();

    void callMessageBox(const QString& info);

    void goToPage(const ScreenPage);
//TODO: success/fail creen
//f - feedback
// to find these functions much easier












// 0 welcome
    void fDisplayWrongCardNum();

// 1 PIN
    void fAddPinChar();
    void fDeletePinChar();
    void fClearPinField();
    void fDisplayWrongPIN(const int triesLeft);

// 2 Menu ???


// 4 transaction data
    void fAddPinChar();
    void fDeletePinChar();
    void fClearPinField();


// 3 balance
    void fDisplayBalance(const int);


// 4 transaction data


// 5 phone data
    void fDisplayWrongPhone();
    void fDisplayWrongGameID();

// 6 get cash
    void fDisplayBadBanknotesAmount(const QString&); // available banktotes

// all input fields
    void fInputFieldAddChar(const InputField, const char);
    void fDeleteFiledChar(const InputField);
    void fClearField(const InputField);

// 7 select charity
    void fDisplaySelectedFond();


// 8 charity data


// 9 select game


// 10 game data
    void fDisplaySelectedGame();








void test();
private slots:



    void handleInputCard();

    void handleZero();
    void handleOne();
    void handleTwo();
    void handleTree();
    void handleFour();
    void handleFive();
    void handleSix();
    void handleSeven();
    void handleEight();
    void handleNine();
    void handleMinus();
    void handlePlus();

    void handleDelete();
    void handleEnter();
    void handleNothing();

    void handleButtonL1();
    void handleButtonL2();
    void handleButtonL3();
    void handleButtonL4();
    void handleButtonR1();
    void handleButtonR2();
    void handleButtonR3();
    void handleButtonR4();

private:
    void timerEvent(QTimerEvent *event);
    int state;
    Ui::MainWindow *ui;
    void attachListeners();
    ATM* atm;
    //void changeAvailable();
    //QMovie *movie;
    //QLabel *lbl;
};
#endif // MAINWINDOW_H
