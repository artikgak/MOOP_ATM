#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QTime>
#include <QMovie>
#include "ATM.h"
#include <QCloseEvent>

//STATES
#include "IdleState.h"
#include "PinState.h"
#include "BalanceState.h"
#include "MenuState.h"
#include "WithdrawState.h"
#include "TransferState.h"
#include "SuccessFailState.h"
#include "AdminState.h"
#include "PhoneState.h"
#include "SelectCharityState.h"

const int MainWindow::MAINWINW = 680;
const int MainWindow::MAINWINH = 550;

MainWindow::MainWindow(ATM& atm, QWidget *parent)
    : QMainWindow(parent)
//    , state(0)
    , ui(new Ui::MainWindow)
    , atm(atm)
    , state(new IdleState(this))
    , destination(Menu)
    , _loaderGif(new QMovie(":images/loader.gif"))
{
    // UI CODE
    ui->setupUi(this);
    MainWindow::setGeometry(330,200,MAINWINW,MAINWINH);
    ui->stackedWidget->setCurrentIndex(0);
    startTimer(1000);   // 1-second timer
    ui->wrongCardNumLabel->setVisible(false);
    _loaderLbl = new QLabel(ui->stackedWidget);
    _loaderLbl->setMovie(_loaderGif);
    _loaderLbl->setAlignment(Qt::AlignCenter);
    _loaderLbl->setAttribute(Qt::WA_TranslucentBackground);
    QRect p =ui->stackedWidget->geometry();
    _loaderLbl->setGeometry(p.x()-50,p.y()-50,p.width(),p.height());
    _loaderLbl->setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowIcon(QIcon(":images/winIcon.png"));

    //Connecting signals from and to ATM for parallel computations
    connectSignals();
}

MainWindow::~MainWindow() {
    delete ui;
    delete state;
}


void MainWindow::closeEvent (QCloseEvent *event)
{
    atm.saveBankToFile();
    event->accept();
}

void MainWindow::timerEvent(QTimerEvent*)
{
    ui->timeLab->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void MainWindow::changeState(WindowState *state) {
  qDebug() << "Context: Transition to " << typeid(*state).name() << ".\n";
  if (this->state != nullptr)
    delete this->state;
  this->state = state;
}

// PUBLIC SLOTS (generally messages FROM ATM - thus unblocking)

void MainWindow::errorMsg(const QString& errorMsg, ScreenPage whereToGo) {
//    ui->succFailLab->setText(errorMsg);
    QMessageBox::critical(this,"Error",errorMsg, QMessageBox::Ok);
    goToPage(whereToGo);
}

void MainWindow::saveBankNotes()
{
atm.bankNotes[0]=ui->spinBox->value();
atm.bankNotes[1]=ui->spinBox_1->value();
atm.bankNotes[2]=ui->spinBox_2->value();
atm.bankNotes[3]=ui->spinBox_3->value();
atm.bankNotes[4]=ui->spinBox_4->value();
atm.saveBankToFile();
}

void MainWindow::showCheque()
{
    QSound::play(":sounds/printer.wav");
    QMessageBox msg;
    msg.setWindowTitle("Print Cheque");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setStyleSheet("QLabel{min-width: 370px;}");
    Cheque cheque = atm.getCheque();
    QString st("");
    st+="=============================\n"
                + QString::fromStdString(cheque.what) +
            "\n=============================\n"

     + "From: " + QString::fromStdString(cheque.from) + '\n';

if(cheque.to!="")
       "To: " + QString::fromStdString(cheque.to) + '\n';

    st+="Amount: " + QString::number(cheque.summa) + "grn\n" +
                 "Date-Time: " + QString::fromStdString(cheque.datetime)
            + "=============================";
    msg.setText(st);
    msg.exec();
}

void MainWindow::goToPage(const ScreenPage sp)
{
    clearCurrentPage();
    int prevSt = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(sp);

    delete state;
    state = nullptr;

    if (sp == Welcome)
        state = new IdleState(this);
    else if (sp == EnterPIN)
        state = new PinState(this);
    else if (sp == Menu)
        state = new MenuState(this);
    else if (sp == Balance)
        state = new BalanceState(this);
    else if (sp == GetCash)
        state = new WithdrawState(this);
    else if (sp == TransactionData)
        state = new TransferState(this);
    else if(sp == SuccessFail)
        state = new SuccessFailState(this, static_cast<ScreenPage>(prevSt));
    else if(sp == Admin)
        state = new AdminState(this);
    else if(sp == SelectCharity)
        state = new SelectCharityState(this,0);
    else if(sp == PhoneData)
        state = new PhoneState(this);

    ui->screenLabel->setText(state->screenName());

}

void MainWindow::displayBankNotes(const int* arr){
    goToPage(Admin);
    ui->spinBox->setValue(arr[0]);
    ui->spinBox_1->setValue(arr[1]);
    ui->spinBox_2->setValue(arr[2]);
    ui->spinBox_3->setValue(arr[3]);
    ui->spinBox_4->setValue(arr[4]);
}

void MainWindow::displayBalance(const std::string& money) {
    goToPage(Balance);
    ui->cashBalanceLabel->setText(QString::fromStdString(money) + "₴");
}

void MainWindow::wrongPin(const uint triesLeft) {
    qDebug() << "tries left" << " " << triesLeft;
    ui->wrongPINLabel->setText("Wrong pin, " + QString::number(triesLeft) + " tries left");
}

// PRIVATE SLOTS (generally messages TO ATM - thus blocking)

void MainWindow::on_inputCard_clicked()
{
    bool ok;
    QString num = QInputDialog::getText(this, tr("Input card"),
                                            tr("Enter card ID:"), QLineEdit::Normal,"", &ok);
    if(!ok) return;

    num = num.replace(" ", "");
    bool valid = emit validateCard(num.toStdString());

    if (valid)
        goToPage(EnterPIN);
    else
        errorMsg("Such card doesn't exist, counterfeit!!", Welcome);
}

void MainWindow::endSession() {
    QMessageBox::information(this, "Card", "Please take out your card");
    emit ejectCard();
    destination = Menu; //TODO DELETE WHEN STATES ARE DONE
}

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
void MainWindow::on_buttonL4_clicked(){state->handleButtonL4();}

void MainWindow::on_buttonR1_clicked(){state->handleButtonR1();}
void MainWindow::on_buttonR2_clicked(){state->handleButtonR2();}
void MainWindow::on_buttonR3_clicked(){state->handleButtonR3();}
void MainWindow::on_buttonR4_clicked(){state->handleButtonR4();}

// ************************************ FeedBackFrom back-end ***************************************************
void MainWindow::displayAvailBankNotes(){
    QString str = "Available banknotes: ";
    for(int i=0; i<5; i++)
        if(atm.bankNotes[i])
            str+= "   " + QString::number(atm.bills[i]);
    ui->availBanknotesLabel->setText(str);
}

void MainWindow::clearCurrentPage(){state->clearCurrentPage();}

void MainWindow::connectSignals() {
    QObject::connect(&atm, &ATM::goToPage, this, &MainWindow::goToPage);
    QObject::connect(&atm, &ATM::errorMsg, this, &MainWindow::errorMsg);
    QObject::connect(&atm, &ATM::wrongPin, this, &MainWindow::wrongPin);

    QObject::connect(this, &MainWindow::validateLogin, &atm, &ATM::validateLogin);
    QObject::connect(this, &MainWindow::getBalance, &atm, &ATM::getBalance);
    QObject::connect(this, &MainWindow::validateCard, &atm, &ATM::validateCard);
    QObject::connect(this, &MainWindow::ejectCard, &atm, &ATM::ejectCard);
    QObject::connect(this, &MainWindow::withdrawMoney, &atm, &ATM::withdrawMoney);
    QObject::connect(this, &MainWindow::transferMoney, &atm, &ATM::transferMoney);
    QObject::connect(this, &MainWindow::rechargePhone, &atm, &ATM::rechargePhone);
    QObject::connect(this, &MainWindow::getCharities, &atm, &ATM::getCharities);
    QObject::connect(this, &MainWindow::payCharity, &atm, &ATM::payCharity);
    QObject::connect(this, &MainWindow::withdMoney, &atm, &ATM::withdMoney);

    QObject::connect(this, &MainWindow::validateAdmin, &atm, &ATM::validateAdmin);
}

void MainWindow::on_adminButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Admin"),
                                         tr("Please scan your id card:"), QLineEdit::Normal,
                                         "", &ok);
    if (!ok) return;
    bool valid = emit validateAdmin(text.toStdString());
    if (valid)
        displayBankNotes(atm.bankNotes);
}

void MainWindow::on_helpServiceButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Help"),
                                         tr("Please enter your number and service worker will contact you soon"
                                            "\nEnter your phone number:"), QLineEdit::Normal,
                                         "", &ok);
    if (!ok || text.isEmpty())
        return;

    QString card = QInputDialog::getText(this, tr("A call"),
                                         tr("Your phone rings, a manager contacts you. "
                                            "\nShe asks you for the card number that you want to block:"), QLineEdit::Normal,
                                         "", &ok);

}
