#include "ATM.h"
#include "mainwindow.h"

#include <iostream>
#include <QString>
#include <functional>
#include <fstream>

using namespace std;

ATM::ATM():
    mainW(nullptr),
    db(*new DataBase("db")), // should be parameter - name of database. if not database is DefaultDB.sqlite
    card(nullptr),
    pin(nullptr),
    file("../ATM_Project/bnkNote.txt"), //
    bankNotes(new int[5])
{
file.open(QIODevice::ReadOnly);
if(!file.isOpen())
    cout << "<banknotes not open>" <<endl;
QString line = file.readLine();
file.close();
QStringList list = line.split(' ');
for(int i=0; i<list.length(); ++i)
bankNotes[i] = list.at(i).toInt();
cout << "<" << line.toStdString() << ">" <<endl;
}


ATM::~ATM() {
    delete card;
    delete[] bankNotes;
}

void ATM::validateAdmin(const string& cardNum){
    assert(card==nullptr); // Card-reader should be empty
    assert(pin==nullptr); // Pin should be empty
    cout  << "Validating admin " << cardNum << endl;
    if (cardNum=="cisco")
        emit displayBankNotes(bankNotes);
}

void ATM::validateCard(const string& cardNum) {
    assert(card==nullptr); // Card-reader should be empty
    assert(pin==nullptr); // Pin should be empty
    cout  << "Validating card: " << cardNum << endl;

    bool retrieved = db.cardExists(cardNum);
    // ///////// TODO
    //retrieved=true;
    if (retrieved) {
        card = new Card(cardNum);
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
    // ///////////// TODO
    //correct=true;
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

void ATM::saveBankToFile()
{
    file.open(QIODevice::WriteOnly | QIODevice::Text |QFile::Truncate);
    QTextStream outStream(&file);
    QString toWrite = QString::number(bankNotes[0]) + ' ' +
                      QString::number(bankNotes[1]) + ' ' +
                      QString::number(bankNotes[2]) + ' ' +
                      QString::number(bankNotes[3]) + ' ' +
                      QString::number(bankNotes[4]);
    file.write(toWrite.toLocal8Bit());
    file.flush();
    file.close();
}
