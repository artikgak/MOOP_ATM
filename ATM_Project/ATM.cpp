#include "ATM.h"
#include "mainwindow.h"

#include <iostream>
#include <QString>
#include <functional>

using namespace std;

ATM::ATM():
    mainW(nullptr),
    db(*new DataBase()),
    card(nullptr),
    pin(nullptr)
{
}


ATM::~ATM() {
    delete card;
}

void ATM::validateCard(const string& cardNum) {
    assert(card==nullptr); // Card-reader should be empty
    assert(pin==nullptr); // Pin should be empty

    cout  << "Validating card: " << cardNum << endl;

    bool retrieved = db.getDataByCardNo(cardNum);
    retrieved =true; //TODO DELETE LATER
    if (retrieved) {
        card = new Card("1234567812345678");  // TODO DELETE LATER;
        emit goToPage(EnterPIN);
    } else {
        emit errorMsg("Such card doesn't exist, counterfeit!!", Welcome);
    }

}
void ATM::validateLogin(const string& entered) {
    assert(card!=nullptr); // There should be a card in card-reader
    assert(pin==nullptr); // Should be no pin at this point

    cout  << "Validating pin: " << pin << endl;
                ;
    bool correct = db.checkPin(card->getNumber(), entered);
    correct =true; // TODO DELETE LATER

    if (correct) { //change to card pin
        this->pin = new string(entered);
        emit goToPage(Menu);
    } else {
        emit wrongPin(0); //TODO add tries left
    }

//    auto f = bind(&ATM::goToPage,this,Menu);
//    validatePinAndEmit(pin,f);
}

void ATM::getBalance() {
    assert(card!=nullptr); // Card should be present
    assert(pin!=nullptr); // Pin should be entered

    double money = db.getMoney(card->getNumber());
    money = 322;
    assert(money!=-1); //If card is present, should be ok

    emit displayBalance(to_string(money));
}

//template<class voidFunc>
//void ATM::validatePinAndEmit(const string& pin, voidFunc toEmit) {
//    assert(card!=nullptr); // There should be a card in card-reader


//    bool correct = db.checkPin(card->getNumber(), pin);
//    correct =true; // DELETE LATER

//    if (correct) { //change to card pin
//        emit toEmit();
//    } else {
//        emit errorMsg("Wrong pin code, try again", EnterPIN);
//    }
//}

void ATM::ejectCard() {
    assert(card!=nullptr); // There should be a card in card-reader
    delete card;
    card = nullptr;

    delete pin;
    pin = nullptr;

    emit goToPage(Welcome);
}
