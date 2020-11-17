#include "ATM.h"
#include "mainwindow.h"

#include <iostream>
#include <QString>
#include <functional>

using namespace std;

ATM::ATM():
    mainW(nullptr),
    db(*new DataBase("db")),
    card(nullptr),
    pin(nullptr)
{
QFile file(":/bankNotes.txt");
file.open(QIODevice::ReadOnly);
QString line = file.readLine();
file.close();
QStringList list = line.split(' ');
for(int i=0; i<list.length(); ++i)
bankNotes[i] = list.at(i).toInt();
}


ATM::~ATM() {
    delete card;
}

void ATM::validateCard(const string& cardNum) {
    assert(card==nullptr); // Card-reader should be empty
    assert(pin==nullptr); // Pin should be empty

    cout  << "Validating card: " << cardNum << endl;

    bool retrieved = db.getDataByCardNo(cardNum);
    //retrieved =true; //TODO DELETE LATER
    if (retrieved) {
        card = new Card("1234123412341231");  // TODO DELETE LATER;
        emit goToPage(EnterPIN);
    } else {
        emit errorMsg("Such card doesn't exist, counterfeit!!", Welcome);
    }

}
void ATM::validateLogin(const string& entered) {
    assert(card!=nullptr); // There should be a card in card-reader
    assert(pin==nullptr); // Should be no pin at this point

    cout  << "Validating pin: " << pin << endl;
    bool correct = db.checkPin(card->getNumber(), entered);
    //correct =true; // TODO DELETE LATER

    if (correct) { //change to card pin
        this->pin = new string(entered);
        emit goToPage(Menu);
    } else {
        emit wrongPin(0); //TODO add tries left
    }
}

void ATM::getBalance() {
    assert(card!=nullptr); // Card should be present
    assert(pin!=nullptr); // Pin should be entered

    double money = db.getMoney(card->getNumber());
    //money = 322;
    assert(money!=-1); //If card is present, should be ok

    emit displayBalance(to_string(money));
}

WithdrawResponse ATM::withdrawMoney(const uint sum) {
    assert(card!=nullptr); // Card should be present
    assert(pin!=nullptr); // Pin should be entered

    double withdraw = db.getMoney(card->getNumber());
    //TOOD WRITE PROPER CODE HERE
    return WOK;
}

TransferResponse ATM::transferMoney(const uint sum, const std::string& cardNum){
    assert(card!=nullptr);
    assert(pin!=nullptr);
    //TRANSFER
    return TOK;
}

void ATM::ejectCard() {
    assert(card!=nullptr); // There should be a card in card-reader
    delete card;
    card = nullptr;

    delete pin;
    pin = nullptr;

    emit goToPage(Welcome);
}
