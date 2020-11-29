#pragma once

#include <QMainWindow>
#include "Utils.h"
#include "Charity.h"
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


void saveBankNotes();
void displayBalance(const std::string& pin);

void wrongPin(const uint);
void displayBankNotes(const int*);
    //void showLoader();
    //void hideLoader();

//TODO: success/fail creen
//f - feedback
// to find these functions much easier
    void displayAvailBankNotes(); // available banktotes

signals:
    bool validateCard(const std::string& cardNum);
    bool validateLogin(const std::string& pin);
    bool validateAdmin(const std::string& id);

    std::string getBalance();
    void ejectCard();

    std::vector<Charity> getCharities(const uint page);
    WithdrawResponse withdrawMoney(const uint sum);
    TransferResponse transferMoney(const uint sum, const std::string& cardNum);

public slots: //TODO make slots and signals not voids but responses
    //more generic ones
    void errorMsg(const QString& errorMsg, ScreenPage whereToGo);
    void goToPage(const ScreenPage);

    //more specific ones
    void endSession();

private slots:
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

    void on_buttonL1_clicked();
    void on_buttonL2_clicked();
    void on_buttonL3_clicked();
    void on_buttonL4_clicked();

    void on_buttonR1_clicked();
    void on_buttonR2_clicked();
    void on_buttonR3_clicked();
    void on_buttonR4_clicked();

    void on_inputCard_clicked();

    void on_adminButton_clicked();

    void on_helpServiceButton_clicked();

private:
    void closeEvent (QCloseEvent *event);
    static const int MAINWINW;
    static const int MAINWINH;
    Ui::MainWindow *ui;
    ATM* atm;

    /* Internal state that will help us better incapsulate the code
     * that goes with every screen (remedy for walls of switch())   */

    WindowState *state;
    friend class WindowState;
    void changeState(WindowState *state);

    ScreenPage _currentScreen;
    ScreenPage destination;//LATER TO BE EXTRACTED TO STATE

    QMovie* _loaderGif;
    QLabel* _loaderLbl;

    void enterNum(char);
    void timerEvent(QTimerEvent *event);

    //Connect signals between MainWindow and ATM
    void connectSignals();

    //Clears current page of previous content before switching to it
    void clearCurrentPage();

    //Block and unblock input before/after sending signals to the ATM
    void blockInput();
    void unblockInput();
};
