#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QTime>
#include <QMovie>
#include "ATM.h"
//#include <QFuture>
//#include <QtCore>
//#include <QtConcurrent/QtConcurrent>
//#include <Task>

const int MAINWINW = 680;
const int MAINWINH = 550;

MainWindow::MainWindow(ATM* atm, QWidget *parent)
    : QMainWindow(parent)
//    , state(0)
    , ui(new Ui::MainWindow)
    , atm(atm)
    ,_currentScreen(Welcome)
    , destination(Menu)
{
    // UI CODE
    ui->setupUi(this);
    attachListeners();
    MainWindow::setGeometry(330,200,MAINWINW,MAINWINH);
    ui->pinField->setReadOnly(true);
    ui->pinField->setMaxLength(8);
    ui->stackedWidget->setCurrentIndex(_currentScreen);
    startTimer(1000);   // 1-second timer
    ui->wrongCardNumLabel->setVisible(false);

    // Tying signals to slots TODO extract into a function
    QObject::connect(atm, &ATM::goToPage, this, &MainWindow::goToPage);
    QObject::connect(atm, &ATM::errorMsg, this, &MainWindow::errorMsg);
    QObject::connect(atm, &ATM::displayBalance, this, &MainWindow::displayBalance);

    QObject::connect(this, &MainWindow::validateLogin, atm, &ATM::validateLogin);
    QObject::connect(this, &MainWindow::validateBalance, atm, &ATM::validateBalance);
    QObject::connect(this, &MainWindow::validateCard, atm, &ATM::validateCard);
    QObject::connect(this, &MainWindow::ejectCard, atm, &ATM::ejectCard);


}

MainWindow::~MainWindow()
{
    //delete movie;
    //delete lbl;
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent*)
{
    ui->timeLab->setText(QTime::currentTime().toString("hh:mm:ss"));
}

//state 0    - no card - enter window
//state 1    - card in, no pin - enter pin window
//state 2    - accaunt menu

//state 11   - enter pin
//state 12   - show balance

//state 21   - enter sum
//state 22   - enter pin

//state 31   - enter card. enter sum.
//state 32   - enter pin

//state 41   - enter phone. enter sum
//state 42   - enter pin

//state 51   - select game  (maybe some pages)
//state 52   - enter accID. enter sum
//state 53   - enter pin

//state 61   - select fond  (maybe some pages)
//state 62   - enter enter sum
//state 63   - enter pin

// state -1   intefrace admin


// widget pages indexes
// 0 welcome
// 1 PIN
// 2 Menu
// 3 balance
// 4 transaction data
// 5 phone data
// 6 get cash
// 7 select charity
// 8 charity data
// 9 select game
// 10 game data

/*void MainWindow::changeAvailable()
{
    if(state==0)
    {
        ui->inputCard->setEnabled(true);
    }
    else if(state==1)
    {
        ui->inputCard->setEnabled(false);
        ui->buttonR1->setEnabled(true);
    }
}*/

void MainWindow::attachListeners() {
    connect(ui->inputCard, SIGNAL (clicked()), this, SLOT (handleInputCard()));

    connect(ui->buttonL1, SIGNAL (clicked()), this, SLOT (handleButtonL1()));
    connect(ui->buttonL2, SIGNAL (clicked()), this, SLOT (handleButtonL2()));
    connect(ui->buttonL3, SIGNAL (clicked()), this, SLOT (handleButtonL3()));
    connect(ui->buttonL4, SIGNAL (clicked()), this, SLOT (handleButtonL4()));

    connect(ui->buttonR1, SIGNAL (clicked()), this, SLOT (handleButtonR1()));
    connect(ui->buttonR2, SIGNAL (clicked()), this, SLOT (handleButtonR2()));
    connect(ui->buttonR3, SIGNAL (clicked()), this, SLOT (handleButtonR3()));
    connect(ui->buttonR4, SIGNAL (clicked()), this, SLOT (handleButtonR4()));
}

// PUBLIC SLOTS (generally messages FROM ATM - thus unblocking)

void MainWindow::errorMsg(const QString& errorMsg, ScreenPage whereToGo) {
    unblockInput();
    QMessageBox::critical(this,"Error",errorMsg, QMessageBox::Ok); // IF artem you want it rework with SuccessFail window :^)))))))))))))))))))))))))))))))))))))))) x-DDdd
    goToPage(whereToGo);
}

void MainWindow::goToPage(const ScreenPage sp)
{
    unblockInput();
    ui->stackedWidget->setCurrentIndex(sp);
    clearCurrentPage();
    _currentScreen=sp;
}

void MainWindow::displayBalance(const std::string& money) {
    unblockInput();
    ui->cashBalanceLabel->setText(QString::fromStdString(money) + "₴");
    goToPage(Balance);
}

// PRIVATE SLOTS (generally messages TO ATM - thus blocking)

void MainWindow::handleInputCard()
{
    bool ok;
    QString num = QInputDialog::getText(this, tr("Input card"),
                                            tr("Enter card ID:"), QLineEdit::Normal,"", &ok);
    if(!ok) return;
    blockInput();

    num = num.replace(" ", "");
    emit validateCard(num.toStdString());
}

/*
void MainWindow::test()
{
    ui->label_4->setText("Changed");
    for(int i=0; i<30000000; ++i)
    for(int l=0; l<30000000; ++l);
}*/

//void MainWindow::handleNothing()
//{
    //showLoader();
    //QFuture<void> future = QtConcurrent::run(this, &MainWindow::test);
    //QThread thr;
    //Task
    //connect(task, QOverload<int, const QString &>::of(&Task::error),
    //    [=](int code, const QString &errorText){ /* ... */ });
    //auto r = std::async(std::launch::async, MainWindow::test));
    //while(r.wait_for(std::chrono::seconds(0))!=std::future_status::ready);
    //r.get();
    //moveToThread(&thr);
    //connect(&thr, SIGNAL(started()), this, SLOT(test())); //cant have parameter sorry, when using connect
    //thr.start();
    //thr.wait(200);
    //future.waitForFinished();
    //hideLoader();
    //future = QtConcurrent::run(this, &MainWindow::hideLoader);
//}

/*
void MainWindow::hideLoader()
{
    movie->stop();
    lbl->hide();
    delete movie;
    delete lbl;
    this->setEnabled(true);
}*/
/*
void MainWindow::showLoader()
{
    this->setEnabled(false);
    lbl = new QLabel(ui->stackedWidget);
    movie = new QMovie(":/images/loader.gif");
    lbl->setMovie(movie);
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setAttribute( Qt::WA_TranslucentBackground, true );
    QRect p = ui->stackedWidget->geometry();
    lbl->setGeometry(p.x()-50,p.y()-50,p.width(),p.height());
    lbl->setWindowFlags(Qt::WindowStaysOnTopHint);
    movie->start();
    lbl->show();
}*/

void MainWindow::enterNum(char num) {
    switch (_currentScreen) {
    case EnterPIN:
        ui->pinField->setText(ui->pinField->text()+num);
        break;
    default:
        break;
    }
}

void   MainWindow::on_button0_clicked() {
    enterNum('0');
} void MainWindow::on_button1_clicked() {
    enterNum('1');
} void MainWindow::on_button2_clicked() {
    enterNum('2');
} void MainWindow::on_button3_clicked() {
    enterNum('3');
} void MainWindow::on_button4_clicked() {
    enterNum('4');
} void MainWindow::on_button5_clicked() {
    enterNum('5');
} void MainWindow::on_button6_clicked() {
    enterNum('6');
} void MainWindow::on_button7_clicked() {
    enterNum('7');
} void MainWindow::on_button8_clicked() {
    enterNum('8');
} void MainWindow::on_button9_clicked() {
    enterNum('9');
}

void MainWindow::on_buttonMinus_clicked() {

}
void MainWindow::on_buttonPlus_clicked() {}

void MainWindow::on_buttonEnter_clicked() {
    switch (_currentScreen) {
    case EnterPIN:
        if (destination == Menu) {
            emit validateLogin(ui->pinField->text().toStdString());
        } else if (destination == Balance) {
            emit validateBalance(ui->pinField->text().toStdString());
        }
        break;
    default:
        break;
    }
}

void MainWindow::on_buttonDelete_clicked() {
    switch (_currentScreen) {
    case EnterPIN:
        ui->pinField->setText("");
        break;
    default:
        break;
    }
}

void MainWindow::on_buttonCorrect_clicked() {
    switch (_currentScreen) {
    case EnterPIN:
        ui->pinField->setText(ui->pinField->text().chopped(1));
        break;
    default:
        break;
    }
}

void MainWindow::on_nothingB_clicked()
{

}


//void MainWindow::handleEnter()
//{
    /*
//if(not valid)
// if(tries) -> you left n-1 ties
//else card blocked
//else go to menu
if(state==1)
{
if(true) // if correct pin
ui->stackedWidget->setCurrentIndex(2);
else
{
// tries -1
}
ui->pinField->setText("");
}*/
//}

void MainWindow::handleButtonL1()
{
    switch (_currentScreen) {
    case Menu:
        destination = Balance;
        goToPage(EnterPIN);
        break;
    default:
        break;
    }
}

void MainWindow::handleButtonL2()
{
    switch (_currentScreen) {
    case Menu:
        goToPage(GetCash);
        break;
    default:
        break;
    }
}

void MainWindow::handleButtonL3()
{

}

void MainWindow::handleButtonL4() {
    switch (_currentScreen) {
    case EnterPIN:
        if (destination == Menu) {
            emit validateLogin(ui->pinField->text().toStdString());
        } else if (destination == Balance) {
            emit validateBalance(ui->pinField->text().toStdString());
        }
        break;

    default:
        break;
    }
}

void MainWindow::handleButtonR1()
{

}

void MainWindow::handleButtonR2()
{

}

void MainWindow::handleButtonR3()
{

}

void MainWindow::handleButtonR4() {
    switch (_currentScreen) {
    case Menu:
    case EnterPIN:
        endSession();
        break;
    case Balance:
        goToPage(Menu);
        break;
    default:
        break;
    }
}

void MainWindow::endSession() {
    QMessageBox::information(this, "Card", "Please take out your card");
    emit ejectCard();
    destination = Menu;
}

//if(not valid)
// if(tries) -> you left n-1 ties
//else card blocked
//else go to menu
/*    if(state==1)
    {
        state=0;
        ui->stackedWidget->setCurrentIndex(0);
        ui->pinField->setText("");
        QMessageBox msgBox;
        msgBox.setText("The card has been ejected. Have a nice day.");
        msgBox.exec();

    }*/
//changeAvailable();
//}

// update front:

//void MainWindow::subscribeATM(ATM* atm)
//{
//this->atm=atm;
//}

void callMessageBox(const QString& info)
{
    QMessageBox msgBox;
    msgBox.setText("The card has been ejected. Have a nice day.");
    msgBox.exec();
}

// ************************************ FeedBackFrom back-end ***************************************************

/*
    Welcome, EnterPIN, Menu, Balance,
    TransactionData, PhoneData, GetCash, SelectCharity,
    CharityData, SelectGame, GameData
 */
void MainWindow::clearCurrentPage()
{
    switch (_currentScreen) {

    case Welcome:
        ui->wrongCardNumLabel->clear();
        break;
    case EnterPIN:
        ui->pinField->clear();
        ui->pinField->setFocus();
        ui->wrongPINLabel->clear();
        break;
    case Menu:
        break;
    case Balance:
        ui->cashBalanceLabel->clear();
        break;
    case TransactionData:
        ui->targetCardField->clear();
        ui->transactionSumField->clear();
        break;
    case PhoneData:
        ui->phoneNumField->clear();
        ui->phoneSumField->clear();
        break;
    case GetCash:
        ui->cashSumField->clear();
        break;
    case SelectCharity:
        break;
    case CharityData:
        ui->selectedFondLabel->clear();
        ui->charitySumField->clear();
        break;
    case SelectGame:
        break;
    case GameData:
        ui->selectedGameLabel->clear();
        ui->gameIDField->clear();
        ui->gameSumField->clear();
        break;
    case SuccessFail:
        ui->succFailLab->clear();
        break;
    }
}

//f - feedback
// to find these functions much easier

// 0 welcome
void MainWindow::fDisplayWrongCardNum()
{
 ui->wrongCardNumLabel->setVisible(true);
}

// 1 PIN
void MainWindow::fAddPinChar()
{
ui->pinField->setText(ui->pinField->text()+'*');
}

void MainWindow::fDeletePinChar()
{
QString st = ui->pinField->text();
ui->pinField->setText(st.length()>0 ? st.left(st.length()-1) : "" );
}

void MainWindow::fClearPinField()
{
ui->pinField->clear();
}

void MainWindow::fDisplayWrongPIN(const int triesLeft)
{
ui->wrongPINLabel->setText("Wrong pin, left " + QString(triesLeft) + " tries");
}

// 2 Menu ???

// 3 balance

// 4 transaction data
    //??select

// 5 phone data
void MainWindow::fDisplayWrongPhone()
{
ui->wrongPhoneNumLabel->setText("Невірний номер телефону");
}

void MainWindow::fDisplayWrongGameID()
{
ui->wrongGameId->setText("Невірнt id профілю");
}


// 6 get cash
void MainWindow::fDisplayBadBanknotesAmount(const QString& st) // available banktotes
{
ui->availBanknotesLabel->setText(st);
}

// all input fields
void MainWindow::fInputFieldAddChar(const InputField inf, const char c)
{
    switch (inf)
    {
    case CashSum:
    {
        QString st = ui->cashSumField->text();
        ui->cashSumField->setText(st+c);
             break;
    }
    case GameAccountID:
    {
        QString st = ui->gameIDField->text();
        ui->gameIDField->setText(st+c);
             break;
    }
    case GameSum:
    {
        QString st = ui->gameSumField->text();
        ui->gameSumField->setText(st+c);
             break;
    }
    case CharitySum:
    {
        QString st = ui->charitySumField->text();
        ui->charitySumField->setText(st+c);
             break;
    }
    case PhoneNum:
    {
        QString st = ui->phoneNumField->text();
        ui->phoneNumField->setText(st+c);
             break;
    }
    case PhoneSum:
    {
        QString st = ui->phoneSumField->text();
        ui->phoneSumField->setText(st+c);
             break;
    }
    case TransactionCard:
    {
        QString st = ui->targetCardField->text();
        ui->targetCardField->setText(st+c);
             break;
    }
    case TransactionSum:
    {
        QString st = ui->transactionSumField->text();
        ui->transactionSumField->setText(st+c);
             break;
    }
    }
}

void MainWindow::fDeleteFiledChar(const InputField inf)
{
    switch (inf)
    {
    case CashSum:
    {
        QString st = ui->cashSumField->text();
        ui->cashSumField->setText(st.length()>0 ? st.left(st.length()-1) : "");
             break;
    }
    case GameAccountID:
    {
        QString st = ui->gameIDField->text();
        ui->gameIDField->setText(st.length()>0 ? st.left(st.length()-1) : "");
             break;
    }
    case GameSum:
    {
        QString st = ui->gameSumField->text();
        ui->gameSumField->setText(st.length()>0 ? st.left(st.length()-1) : "");
             break;
    }
    case CharitySum:
    {
        QString st = ui->charitySumField->text();
        ui->charitySumField->setText(st.length()>0 ? st.left(st.length()-1) : "");
             break;
    }
    case PhoneNum:
    {
        QString st = ui->phoneNumField->text();
        ui->phoneNumField->setText(st.length()>0 ? st.left(st.length()-1) : "");
             break;
    }
    case PhoneSum:
    {
        QString st = ui->phoneSumField->text();
        ui->phoneSumField->setText(st.length()>0 ? st.left(st.length()-1) : "");
             break;
    }
    case TransactionCard:
    {
        QString st = ui->targetCardField->text();
        ui->targetCardField->setText(st.length()>0 ? st.left(st.length()-1) : "");
             break;
    }
    case TransactionSum:
    {
        QString st = ui->transactionSumField->text();
        ui->transactionSumField->setText(st.length()>0 ? st.left(st.length()-1) : "");
             break;
    }
    }
}

void MainWindow::fClearField(const InputField inf)
{
    switch (inf)
    {
    case CashSum:
    {
        ui->cashSumField->clear();
             break;
    }
    case GameAccountID:
    {
        ui->gameIDField->clear();
             break;
    }
    case GameSum:
    {
        ui->gameSumField->clear();
             break;
    }
    case CharitySum:
    {
        ui->charitySumField->clear();
             break;
    }
    case PhoneNum:
    {
        ui->phoneNumField->clear();
             break;
    }
    case PhoneSum:
    {
        ui->phoneSumField->clear();
             break;
    }
    case TransactionCard:
    {
        ui->targetCardField->clear();
             break;
    }
    case TransactionSum:
    {
        ui->transactionSumField->clear();
             break;
    }
    }
}


// 7 select charity
    //list of fonds


// 8 charity data
void MainWindow::fDisplaySelectedFond(const QString& str)
{
    ui-> selectedFondLabel->setText(str);
}


// 9 select game
//list of games

// 10 game data
void MainWindow::fDisplaySelectedGame(const QString& str)
{
    ui-> selectedGameLabel->setText(str);
}

void MainWindow::fDisplaySuccessFail(const QString& str)
{
    ui->succFailLab->setText(str);
}
