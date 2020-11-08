#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>



const int MAINWINW = 500;
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

//state 0    - no card
//state 1    - card in, no pin
//state 2    - accaunt menu

void MainWindow::changeAvailable()
{
    if(state==0)
    {
        ui->inputCard->setEnabled(true);
    }
    else if(state==1)
    {
        ui->inputCard->setEnabled(false);
        ui->buttonBack->setEnabled(true);
    }
}

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
    connect(ui->ejectCard, SIGNAL (clicked()), this, SLOT (handleEjectCard()));
    connect(ui->buttonDelete, SIGNAL (clicked()), this, SLOT (handleDelete()));
    connect(ui->buttonEnter, SIGNAL (clicked()), this, SLOT (handleEnter()));
    connect(ui->buttonBack, SIGNAL (clicked()), this, SLOT (handleBack()));

}

void MainWindow::handleInputCard()
{
    QString text = QInputDialog::getText(this, tr("Ваша карта"),
                                            tr("Введіть номер:"), QLineEdit::Normal);
    if(true)
    {
        state=1;
        changeAvailable();
    }
// if ok nomer-> set availbale inteface
// else message box wrong card number
}

void MainWindow::handleEjectCard()
{
ui->stackedWidget->setCurrentIndex(0);
state = 0;
changeAvailable();
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
ui->stackedWidget->setCurrentIndex(1);
else
{
// tries -1
}
ui->pinField->setText("");
}
}

void MainWindow::handleBack()
{
//if(not valid)
// if(tries) -> you left n-1 ties
//else card blocked
//else go to menu
    if(state==1)
    {
        state=0;
        QMessageBox msgBox;
        msgBox.setText("The card has been ejected. Have a nice day.");
        msgBox.exec();
        ui->pinField->setText("");
    }
changeAvailable();
}
