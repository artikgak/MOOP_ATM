#pragma once

#include <QMainWindow>
#include "Utils.h"
#include "Card.h"
#include <QLabel>
#include <QThread>

class WindowState;
class Test_Front;
class ATM;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;
public:
    friend Test_Front;
    MainWindow(ATM* atm, QWidget *parent = nullptr);
    ~MainWindow();
//    void subscribeATM(ATM*);



    //void showLoader();
    //void hideLoader();

//    void callMessageBox(const QString& info);
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

// 3 balance
    void fDisplayBalance(const int);

// 4 transaction data
    //??select

    /*void fAddTrasfCardNumChar(char c);
    void fDeleteTrasfCardNumChar();
    void fClearTrasfCardNumField();

    void fAddTransferSumChar(char c);
    void fDeleteTransferSumChar();
    void fClearTransferSumField();
*/
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
    //list of fonds


// 8 charity data
    void fDisplaySelectedFond(const QString& str);

// 9 select game
//list of games

// 10 game data
    void fDisplaySelectedGame(const QString& str);

void fDisplaySuccessFail(const QString& str);






void test();

signals:
    void validateCard(const std::string& cardNum);
    void validateLogin(const std::string& pin);

    void getBalance();
    void ejectCard();

public slots:
    //more generic ones
    void errorMsg(const QString& errorMsg, ScreenPage whereToGo);
    void goToPage(const ScreenPage);

    //more specific ones
    void displayBalance(const std::string& pin);

private slots:

    void handleInputCard();

    void handleButtonL1();
    void handleButtonL2();
    void handleButtonL3();
    void handleButtonL4();
    void handleButtonR1();
    void handleButtonR2();
    void handleButtonR3();
    void handleButtonR4();

    void on_button0_clicked();
    void on_button1_clicked();
    void on_button2_clicked();
    void on_button3_clicked();
    void on_button4_clicked();
    void on_button5_clicked();
    void on_button6_clicked();
    void on_button7_clicked();
    void on_button8_clicked();
    void on_button9_clicked();

    void on_buttonMinus_clicked();
    void on_buttonPlus_clicked();

    void on_buttonEnter_clicked();
    void on_buttonDelete_clicked();
    void on_buttonCorrect_clicked();
    void on_buttonNothing_clicked();

private:
    Ui::MainWindow *ui;
    ATM* atm;

    /* Internal state that will help us better incapsulate the code
     * that goes with every screen (remedy for walls of switch())   */

    WindowState *state;
    friend class WindowState;
    void changeState(WindowState *state);

    ScreenPage _currentScreen;
    ScreenPage destination;//LATER TO BE EXTRACTED TO STATE

    void enterNum(char);
    void endSession();
    void timerEvent(QTimerEvent *event);
    void attachListeners();

    //Clears current page of previous content before switching to it
    void clearCurrentPage();

    //Block and unblock input before/after sending signals to the ATM
    void blockInput() {};
    void unblockInput() {};
};
