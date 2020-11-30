#include "ATM.h"
#include "mainwindow.h"

#include <iostream>
#include <QString>
#include <functional>
#include <fstream>
#include <cassert>
#include <iomanip>
#include <sstream>
#include "DataBase.h"
#include <time.h>

using namespace std;

const int ATM::bills[] = {20,50,100,200,500};

ATM::ATM():
        mainW(nullptr),
        db(*new DataBase("db")), // should be parameter - name of database. if not database is DefaultDB.sqlite
        card(nullptr),
        pin(nullptr),
        file("../ATM_Project/bnkNote.txt"),
        //file("/Users/akreidun/Desktop/MOOP_ATM/ATM_Project/bnkNote.txt"),
        bankNotes(new int[5]),
        bnkOnPot(new int[5]){
    fullDB(db);
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
        cout << "<banknotes not open>" <<endl;
    QString line = file.readLine();
    file.close();

    QStringList list = line.split(' ');
    for(int i=0; i<list.length(); ++i)
        bankNotes[i] = list.at(i).toInt();
    for(int i=0; i<5; ++i)bnkOnPot[i]=0;
    cout << "<" << line.toStdString() << ">" <<endl;
}


ATM::~ATM() {
    delete card;
    delete[] bankNotes;
    delete[] bnkOnPot;
}

void ATM::takeMoney()
{
    for(int i=0;i<5;++i)
        bnkOnPot[i]=0;
}

bool ATM::validateAdmin(const string& id){
    assert(card == nullptr); // Card-reader should be empty
    assert(pin == nullptr); // Pin should be empty

    cout  << "Validating admin " << id << endl;
    return db.adminExists(id);
}

bool ATM::validateCard(const string& cardNum) {
    assert(card == nullptr); // Card-reader should be empty
    assert(pin == nullptr); // Pin should be empty

    cout  << "Validating card: " << cardNum << endl;
    bool retrieved = db.cardExists(cardNum);

    if (retrieved) card = new string(cardNum);

    return (retrieved);
}

bool ATM::validateLogin(const string& entered) {
    assert(card != nullptr); // There should be a card in card-reader
    assert(pin == nullptr); // Should be no pin at this point

    cout  << "Validating pin: " << entered << endl;
    bool correct = db.checkPin(*card, entered);
    if (correct) pin = new string(entered);
    else {
        auto tries = db.getTries(*card);
        emit wrongPin(tries);

        if (tries <= 0) {
            emit errorMsg("Too many wrong tries. *You hear that your card is consumed by ATM*", Welcome);
            card = nullptr;
        }
    }
    return correct;
}

std::string ATM::getBalance() {
    assert(card != nullptr); // Card should be present
    assert(pin != nullptr); // Pin should be entered

    double money = db.getMoney(*card);
    assert(money != -1); //If card is present, should be ok
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << money;
    return stream.str();
}

WithdrawResponse ATM::withdrawMoney(const uint sum) {
    assert(card != nullptr); // Card should be present
    assert(pin != nullptr); // Pin should be entered

    // work with banknotes
    size_t allMoney = 0;
    for (int i = 0; i<5; ++i)
        allMoney += bankNotes[i] * bills[i];

    if(allMoney < sum)
        return AtmNoMoney;

    double withdraw = db.getMoney(*card);
    // if bad credit limit
    if(withdraw < sum)
        return UserNoMoney;


    int summa = sum;
    for(int i=4; i>=0; --i)
        while(summa>=bills[i] && (bankNotes[i]-bnkOnPot[i])>0)
        {
            summa-=bills[i];
            bnkOnPot[i]++;
        }

    if(summa)
        return AtmNoBills;

    for(int i=0; i<5; ++i)
        bankNotes[i]-=bnkOnPot[i];


    db.addMoney(*card, -summa);

    createCheque("Withdraw",  "", sum);
    return WOK;
}

PhoneResponse ATM::rechargePhone(const uint sum, const std::string& phone) {
    assert(card != nullptr); // Card should be present
    assert(pin != nullptr); // Pin should be entered

    double money = db.getMoney(*card);
    // if bad credit limit
    if(money < sum)
        return NotEnoughMoney;

    createCheque("Top-up phone", phone, sum);

    return db.addMoney(*card, -sum) ? POK : PFail;
}

void ATM::recountBankNotes(const int sum, const int billsSize){
    int rest = sum;
    int i = billsSize;
    while(rest)
    {
        while(!(rest % bills[i]) && bankNotes[i])
        {
            rest -= bills[i];
            bankNotes[i]--;
        }
        i--;
    }
}

TransferResponse ATM::transferMoney(const uint sum, const std::string& cardNum){
    assert(card != nullptr);
    assert(pin != nullptr);

    if(cardNum == *card )
        return SAMECARD;

    if(!db.cardExists(cardNum))
        return TARGETCARDNOTFOUND;

    if (db.getMoney(*card) < sum)
        return NotEnoughMonet;

    int summa = sum;
    bool succ = db.addMoney(*card, -summa);
    if (!succ) return FAIL;

    succ = db.addMoney(cardNum, sum);
    if (!succ) return FAIL;

    createCheque("Transfer",  std::string(cardNum), sum);
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

std::vector<Charity> ATM::getCharities(const uint page) {
    std::vector<Charity> charities = db.getCharities(page, 4);

    for (auto current : charities) {
        std::cout << '\t' << current.id << ' ' << current.name << '\n';
    }

    return charities;
}

TransferResponse ATM::payCharity(uint id, uint sum) {
    assert(card != nullptr);
    qDebug() << "Transfering to " << id << " $" << sum;
    int summa = sum;
    bool resp = db.addMoney(*card, -summa);

    if(resp)
    {
    createCheque("Charity donation", std::string(getCharities(0).at(id).name), sum);
    return TOK;
    }
    return NotEnoughMonet;
}


QString ATM::withdMoney()
{
    QString st;
    for(int i=0; i<5; ++i)
        if(bnkOnPot[i]>0)
            st+= QString::number(bills[i]) + "grn - " +
                    QString::number(bnkOnPot[i]) + "banknotes\n" ;

    takeMoney();
    return st;
}

void ATM::createCheque(std::string what, std::string to, int sum)
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    std::string datetime(asctime(timeinfo));
    /* what
     * *card      - card FROM
     * cardNum    - card TO
     * sum        - summa
     * date, time - date, time
     */
    cheque.what = what;
    cheque.from = std::string(*card);
    cheque.to = to;
    cheque.summa = sum;
    cheque.datetime = datetime;

    std::cout << "From " << cheque.from << '\n' <<
                 "To " << cheque.to << '\n' <<
                 "Amount " << cheque.summa << '\n' <<
                 "When: " << cheque.datetime << '\n' << std::flush;
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
