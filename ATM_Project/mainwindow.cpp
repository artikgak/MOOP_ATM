#include "mainwindow.h"
#include "ui_mainwindow.h"

const int MAINWINW = 500;
const int MAINWINH = 550;
const int GRIDBUTW = 150;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setGeometry(330,200,MAINWINW,MAINWINH);
}

MainWindow::~MainWindow()
{
    delete ui;
}

