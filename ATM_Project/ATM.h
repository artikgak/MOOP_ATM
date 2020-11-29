#pragma once

#include "Utils.h"
#include "DataBase.h"
#include "QObject"
#include "Charity.h"
#include "Cheque.h"

class Test_Front;
class MainWindow;

class ATM : public QObject
{
    Q_OBJECT
private:
    /* Class variables */
    MainWindow* mainW;

    DataBase& db;
    std::string* card;
    std::string* pin;
    ATMState state;
    Cheque cheque{"", "", 0, ""};

    ATM& operator=(ATM&) = delete;
    ATM(ATM&) = delete;

    QFile file;
//    template<class voidFunc>
//    void validatePinAndEmit(const std::string& pin, voidFunc toEmit);

    void recountBankNotes(const int sum, const int billsSize=5);
public:
inline const Cheque& getCheque() const {return cheque;}
static const int bills[5];
void saveBankToFile();
int* bankNotes;

    friend Test_Front;
    ATM();
    ~ATM();

// Signals received from UI
public slots:
    WithdrawResponse withdrawMoney(const uint sum);
    TransferResponse transferMoney(const uint sum, const std::string& cardNum);
    PhoneResponse rechargePhone(const uint sum);
    bool validateAdmin(const std::string& adminID);
    bool validateCard(const std::string& cardNum);
    bool validateLogin(const std::string& pin);
    std::string getBalance();

    bool payCharity(uint id, uint sum);
    std::vector<Charity> getCharities(const uint page);
    void ejectCard();

// Signals sent to UI
signals:
    void errorMsg(const QString& errorMsg, ScreenPage whereToGo);
    void goToPage(const ScreenPage);
    void wrongPin(const uint triesLeft);
    void displayBankNotes(const int*);
};

