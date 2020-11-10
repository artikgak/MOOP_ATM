#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QTime>
#include <QMovie>
//#include <QFuture>
//#include <QtCore>
//#include <QtConcurrent/QtConcurrent>
//#include <Task>

const int MAINWINW = 680;
const int MAINWINH = 550;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , state(0)
    , ui(new Ui::MainWindow)
    , atm(nullptr)
    ,_currentScreen(Welcome)
{
    ui->setupUi(this);
    attachListeners();
    MainWindow::setGeometry(330,200,MAINWINW,MAINWINH);
    ui->pinField->setReadOnly(true);
    ui->pinField->setMaxLength(8);
    ui->stackedWidget->setCurrentIndex(_currentScreen);
    startTimer(1000);   // 1-second timer
    ui->wrongCardNumLabel->setVisible(false);
}

MainWindow::~MainWindow()
{
    //delete movie;
    //delete lbl;
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent * event)
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

void MainWindow::attachListeners()
{
    connect(ui->button0,   SIGNAL (clicked()), this, SLOT (handleZero()));
    connect(ui->button1,   SIGNAL (clicked()), this, SLOT (handleOne()));
    connect(ui->button2,   SIGNAL (clicked()), this, SLOT (handleTwo()));
    connect(ui->button3,   SIGNAL (clicked()), this, SLOT (handleTree()));
    connect(ui->button4,   SIGNAL (clicked()), this, SLOT (handleFour()));
    connect(ui->button5,   SIGNAL (clicked()), this, SLOT (handleFive()));
    connect(ui->button6,   SIGNAL (clicked()), this, SLOT (handleSix()));
    connect(ui->button7,   SIGNAL (clicked()), this, SLOT (handleSeven()));
    connect(ui->button8,   SIGNAL (clicked()), this, SLOT (handleEight()));
    connect(ui->button9,   SIGNAL (clicked()), this, SLOT (handleNine()));
    connect(ui->buttonMinus,   SIGNAL (clicked()), this, SLOT (handleMinus()));
    connect(ui->buttonPlus,    SIGNAL (clicked()), this, SLOT (handlePlus()));
    connect(ui->inputCard, SIGNAL (clicked()), this, SLOT (handleInputCard()));

    connect(ui->buttonDelete, SIGNAL (clicked()), this, SLOT (handleDelete()));
    connect(ui->buttonEnter, SIGNAL (clicked()), this, SLOT (handleEnter()));

    connect(ui->buttonL1, SIGNAL (clicked()), this, SLOT (handleButtonL1()));
    connect(ui->buttonL2, SIGNAL (clicked()), this, SLOT (handleButtonL2()));
    connect(ui->buttonL3, SIGNAL (clicked()), this, SLOT (handleButtonL3()));
    connect(ui->buttonL4, SIGNAL (clicked()), this, SLOT (handleButtonL4()));

    connect(ui->buttonR1, SIGNAL (clicked()), this, SLOT (handleButtonR1()));
    connect(ui->buttonR2, SIGNAL (clicked()), this, SLOT (handleButtonR2()));
    connect(ui->buttonR3, SIGNAL (clicked()), this, SLOT (handleButtonR3()));
    connect(ui->buttonR4, SIGNAL (clicked()), this, SLOT (handleButtonR4()));


    connect(ui->nothingB, SIGNAL (clicked()), this, SLOT (handleNothing()));
}

void MainWindow::handleInputCard()
{
    QString text = QInputDialog::getText(this, tr("Input card"),
                                            tr("Enter card ID:"), QLineEdit::Normal);
    //send text to back-end
    //end remove code under
    if(text.length()>5)
    {
        state=1;
        ui->stackedWidget->setCurrentIndex(1);
        //changeAvailable();
    }



// if ok nomer-> set availbale inteface
// else message box wrong card number
}
/*
void MainWindow::test()
{
    ui->label_4->setText("Changed");
    for(int i=0; i<30000000; ++i)
    for(int l=0; l<30000000; ++l);
}*/

void MainWindow::handleNothing()
{
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

void MainWindow::handleZero()
{
ui->pinField->setText(ui->pinField->text()+'*');
}

void MainWindow::handleOne()
{
// if state == enter pin
  if(state==1)
  ui->pinField->setText(ui->pinField->text()+'*');
}

void MainWindow::handleTwo()
{
      if(state==1)
ui->pinField->setText(ui->pinField->text()+'*');
//add number in ATM
}

void MainWindow::handleTree()
{
      if(state==1)
ui->pinField->setText(ui->pinField->text()+'*');
}

void MainWindow::handleFour()
{
      if(state==1)
ui->pinField->setText(ui->pinField->text()+'*');
}

void MainWindow::handleFive()
{
      if(state==1)
ui->pinField->setText(ui->pinField->text()+'*');
}

void MainWindow::handleSix()
{
      if(state==1)
ui->pinField->setText(ui->pinField->text()+'*');
}

void MainWindow::handleSeven()
{
ui->pinField->setText(ui->pinField->text()+'*');
}

void MainWindow::handleEight()
{
ui->pinField->setText(ui->pinField->text()+'*');
}

void MainWindow::handleNine()
{
ui->pinField->setText(ui->pinField->text()+'*');
}

void MainWindow::handleMinus()
{

}

void MainWindow::handlePlus()
{

}

void MainWindow::handleDelete()
{
   /* QString st(ui->pinField->text());
    ui->pinField->setText(st.left(st.length()-1));*/

}

void MainWindow::handleEnter()
{
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
}

void MainWindow::handleButtonL1()
{

}

void MainWindow::handleButtonL2()
{

}

void MainWindow::handleButtonL3()
{

}

void MainWindow::handleButtonL4()
{

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

void MainWindow::handleButtonR4()
{
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
}

// update front:

void MainWindow::subscribeATM(ATM* atm)
{
this->atm=atm;
}

void callMessageBox(const QString& info)
{
    QMessageBox msgBox;
    msgBox.setText("The card has been ejected. Have a nice day.");
    msgBox.exec();
}

// ************************************ FeedBackFrom back-end ***************************************************
void MainWindow::goToPage(const ScreenPage sp)
{
ui->stackedWidget->setCurrentIndex(sp);
clearCurrentPage();
_currentScreen=sp;
}
/*
    Welcome, EnterPIN, Menu, Balance,
    TransactionData, PhoneData, GetCash, SelectCharity,
    CharityData, SelectGame, GameData
 */
void MainWindow::clearCurrentPage()
{
    switch (_currentScreen)
    {
    case Welcome:
    {
        ui->wrongCardNumLabel->clear();
        break;
    }
    case EnterPIN:
    {
        ui->pinField->clear();
        ui->wrongPINLabel->clear();
        break;
    }
    case Menu:
    {
        break;
    }
    case Balance:
    {
        ui->cashBalanceLabel->clear();
        break;
    }
    case TransactionData:
    {
        ui->targetCardField->clear();
        ui->transactionSumField->clear();
        break;
    }
    case PhoneData:
    {
        ui->phoneNumField->clear();
        ui->phoneSumField->clear();
        break;
    }
    case GetCash:
    {
        ui->cashSumField->clear();
        break;
    }
    case SelectCharity:
    {
        break;
    }
    case CharityData:
    {
        ui->selectedFondLabel->clear();
        ui->charitySumField->clear();
        break;
    }
    case SelectGame:
    {
        break;
    }
    case GameData:
    {
        ui->selectedGameLabel->clear();
        ui->gameIDField->clear();
        ui->gameSumField->clear();
        break;
    }
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
void MainWindow::fDisplayBalance(const int money)
{
    ui->cashBalanceLabel->setText(QString(money)+ "₴");
}


// 4 transaction data
    //??select

// 5 phone data
void MainWindow::fDisplayWrongPhone()
{

}

void MainWindow::fDisplayWrongGameID()
{

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

