#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Utils.h"
#include "Card.h"
#include <QLabel>
#include <QThread>

class ATM;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;
public:
    MainWindow(ATM* atm, QWidget *parent = nullptr);
    ~MainWindow();
//    void subscribeATM(ATM*);



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
    void validateCard(Card card);

public slots:
    void errorMsg(const QString& errorMsg, ScreenPage whereToGo);
    void cardConfirmation();

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
    ScreenPage _currentScreen;
    void clearCurrentPage();
    //void changeAvailable();
    //QMovie *movie;
    //QLabel *lbl;
    void blockInput() {};
    void unblockInput() {};
};
#endif // MAINWINDOW_H
