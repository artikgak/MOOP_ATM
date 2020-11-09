#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QTime>


const int MAINWINW = 680;
const int MAINWINH = 550;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , state(0)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    attachListeners();
    MainWindow::setGeometry(330,200,MAINWINW,MAINWINH);
    ui->pinField->setReadOnly(true);
    ui->pinField->setMaxLength(8);
    startTimer(1000);   // 1-second timer
}

MainWindow::~MainWindow()
{
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
    QString text = QInputDialog::getText(this, tr("Ваша карта"),
                                            tr("Введіть номер:"), QLineEdit::Normal);
    if(true)
    {
        state=1;
        ui->stackedWidget->setCurrentIndex(1);
        //changeAvailable();
    }
// if ok nomer-> set availbale inteface
// else message box wrong card number
}

void MainWindow::handleNothing()
{

}

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
    QString st(ui->pinField->text());
    ui->pinField->setText(st.left(st.length()-1));
}

void MainWindow::handleEnter()
{
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
}
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
void callMessageBox(const QString& info)
{
    QMessageBox msgBox;
    msgBox.setText("The card has been ejected. Have a nice day.");
    msgBox.exec();
}
