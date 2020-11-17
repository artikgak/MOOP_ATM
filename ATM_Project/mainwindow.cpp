#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QTime>
#include <QMovie>
#include "ATM.h"

//STATES
#include "IdleState.h"
#include "PinState.h"
#include "BalanceState.h"
#include "MenuState.h"
#include "WithdrawState.h"
#include "TransferState.h"
#include "SuccessFailState.h"


const int MainWindow::MAINWINW = 680;
const int MainWindow::MAINWINH = 550;

MainWindow::MainWindow(ATM* atm, QWidget *parent)
    : QMainWindow(parent)
//    , state(0)
    , ui(new Ui::MainWindow)
    , atm(atm)
    , state(new IdleState())
    ,_currentScreen(Welcome)
    , destination(Menu)
    , _loaderGif(new QMovie(":images/loader.gif"))
{
    state->set_context(this);
    // UI CODE
    ui->setupUi(this);
    MainWindow::setGeometry(330,200,MAINWINW,MAINWINH);
    ui->stackedWidget->setCurrentIndex(_currentScreen);
    startTimer(1000);   // 1-second timer
    ui->wrongCardNumLabel->setVisible(false);
    _loaderLbl = new QLabel(ui->stackedWidget);
    _loaderLbl->setMovie(_loaderGif);
    _loaderLbl->setAlignment(Qt::AlignCenter);
    _loaderLbl->setAttribute(Qt::WA_TranslucentBackground);
    QRect p =ui->stackedWidget->geometry();
    _loaderLbl->setGeometry(p.x()-50,p.y()-50,p.width(),p.height());
    _loaderLbl->setWindowFlags(Qt::WindowStaysOnTopHint);

    // Tying signals to slots TODO extract into a function
    connectSignals();

}

MainWindow::~MainWindow()
{
    //delete movie;
    //delete lbl;
    delete ui;
    delete state;
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

void MainWindow::changeState(WindowState *state) {
  qDebug() << "Context: Transition to " << typeid(*state).name() << ".\n";
  if (this->state != nullptr)
    delete this->state;
  this->state = state;
  this->state->set_context(this);
}

// PUBLIC SLOTS (generally messages FROM ATM - thus unblocking)

void MainWindow::errorMsg(const QString& errorMsg, ScreenPage whereToGo) {
    QMessageBox::critical(this,"Error",errorMsg, QMessageBox::Ok); // IF artem you want it rework with SuccessFail window :^)))))))))))))))))))))))))))))))))))))))) x-DDdd
    goToPage(whereToGo);
    unblockInput();
}

void MainWindow::goToPage(const ScreenPage sp)
{
    clearCurrentPage();
    int prevSt = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(sp);

    delete state;
    state = nullptr;

    if (sp == Welcome)
        state = new IdleState();
    else if (sp == EnterPIN)
        state = new PinState();
    else if (sp == Menu)
        state = new MenuState();
    else if (sp == Balance)
        state = new BalanceState();
    else if (sp == GetCash)
        state = new WithdrawState();
    else if (sp == TransactionData)
        state = new TransferState();
    else if(sp == SuccessFail)
        state = new SuccessFailState(static_cast<ScreenPage>(prevSt));

    state->set_context(this);



    //clearCurrentPage();
    ui->screenLabel->setText(state->screenName());

    _currentScreen=sp; // TODO delete when ready
    unblockInput();
}

void MainWindow::displayBalance(const std::string& money) {
    goToPage(Balance);
    ui->cashBalanceLabel->setText(QString::fromStdString(money) + "₴");
    unblockInput();
}

void MainWindow::wrongPin(const uint triesLeft) {
    ui->wrongPINLabel->setText("Wrong pin, " + QString::number(triesLeft) + " tries left");
}

// PRIVATE SLOTS (generally messages TO ATM - thus blocking)

void MainWindow::on_inputCard_clicked()
{
    blockInput();
    bool ok;
    QString num = QInputDialog::getText(this, tr("Input card"),
                                            tr("Enter card ID:"), QLineEdit::Normal,"", &ok);
    if(!ok){ unblockInput(); return;}

    num = num.replace(" ", "");
    emit validateCard(num.toStdString());
}

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

//  Just binding to State
void MainWindow::on_button0_clicked() {state->enterNum('0');}
void MainWindow::on_button1_clicked() {state->enterNum('1');}
void MainWindow::on_button2_clicked() {state->enterNum('2');}
void MainWindow::on_button3_clicked() {state->enterNum('3');}
void MainWindow::on_button4_clicked() {state->enterNum('4');}
void MainWindow::on_button5_clicked() {state->enterNum('5');}
void MainWindow::on_button6_clicked() {state->enterNum('6');}
void MainWindow::on_button7_clicked() {state->enterNum('7');}
void MainWindow::on_button8_clicked() {state->enterNum('8');}
void MainWindow::on_button9_clicked() {state->enterNum('9');}

void MainWindow::on_buttonMinus_clicked() {state->handleButtonMinus();}
void MainWindow::on_buttonPlus_clicked() {state->handleButtonPlus();}

void MainWindow::on_buttonEnter_clicked() {state->handleButtonEnter();}
void MainWindow::on_buttonDelete_clicked() {state->handleButtonDelete();}
void MainWindow::on_buttonCorrect_clicked() {state->handleButtonCorrect();}
void MainWindow::on_buttonNothing_clicked(){state->handleButtonNothing();}

void MainWindow::on_buttonL1_clicked(){state->handleButtonL1();}
void MainWindow::on_buttonL2_clicked(){state->handleButtonL2();}
void MainWindow::on_buttonL3_clicked(){state->handleButtonL3();}
void MainWindow::on_buttonL4_clicked(){
    blockInput();
    state->handleButtonL4();
}

void MainWindow::on_buttonR1_clicked(){state->handleButtonR1();}
void MainWindow::on_buttonR2_clicked(){state->handleButtonR2();}
void MainWindow::on_buttonR3_clicked(){state->handleButtonR3();}

void MainWindow::on_buttonR4_clicked() {
    state->handleButtonR4();
    return;
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
    destination = Menu; //TODO DELETE WHEN STATES ARE DONE
}

void MainWindow::blockInput()
{
//_loaderGif->start();
//_loaderLbl->show();
}

void MainWindow::unblockInput()
{
//_loaderGif->stop();
//_loaderLbl->hide();
}

// ************************************ FeedBackFrom back-end ***************************************************

void MainWindow::clearCurrentPage(){state->clearCurrentPage();}

void MainWindow::connectSignals() {
    QObject::connect(atm, &ATM::goToPage, this, &MainWindow::goToPage);
    QObject::connect(atm, &ATM::errorMsg, this, &MainWindow::errorMsg);
    QObject::connect(atm, &ATM::displayBalance, this, &MainWindow::displayBalance);
    QObject::connect(atm, &ATM::wrongPin, this, &MainWindow::wrongPin);

    QObject::connect(this, &MainWindow::validateLogin, atm, &ATM::validateLogin);
    QObject::connect(this, &MainWindow::getBalance, atm, &ATM::getBalance);
    QObject::connect(this, &MainWindow::validateCard, atm, &ATM::validateCard);
    QObject::connect(this, &MainWindow::ejectCard, atm, &ATM::ejectCard);
    QObject::connect(this, &MainWindow::withdrawMoney, atm, &ATM::withdrawMoney);
    QObject::connect(this, &MainWindow::transferMoney, atm, &ATM::transferMoney);
}
