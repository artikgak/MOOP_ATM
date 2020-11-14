#include "ATM.h"
#include "mainwindow.h"

#include <iostream>
#include <QString>
#include <functional>

using namespace std;

ATM::ATM():
    mainW(nullptr),
    db(*new DataBase()),
    card(nullptr)
{
}


ATM::~ATM() {
    delete card;
}

void ATM::validateCard(const string& cardNum) {
    assert(card==nullptr); // Card-reader should be empty

    cout << "Validating card " << cardNum << endl; // DEBUG INFO
    bool retrieved = db.getDataByCardNo(cardNum);
    retrieved =true; // DELETE LATER
    if (retrieved) {
        card = new Card("1234567812345678");  //DELETE LATER;
        emit goToPage(EnterPIN);
    } else {
        emit errorMsg("Such card doesn't exist, counterfeit!!", Welcome);
    }

}
void ATM::validateLogin(const string& pin) {
    auto f = bind(&ATM::goToPage,this,Menu);
    validatePinAndEmit(pin,f);
}

void ATM::validateBalance(const string& pin) {
    string money = to_string(db.getMoney(card->getNumber()));
    auto f = bind(&ATM::displayBalance,this, money);
    validatePinAndEmit(pin, f);
}

template<class voidFunc>
void ATM::validatePinAndEmit(const string& pin, voidFunc toEmit) {
    assert(card!=nullptr); // There should be a card in card-reader

    bool correct = db.checkPin(card->getNumber(), pin);
    correct =true; // DELETE LATER

    if (correct) { //change to card pin
        emit toEmit();
    } else {
        emit errorMsg("Wrong pin code, try again", EnterPIN);
    }
}



void ATM::ejectCard() {
    assert(card!=nullptr); // There should be a card in card-reader
    delete card;
    card = nullptr;
    emit goToPage(Welcome);
}
