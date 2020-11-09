#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void callMessageBox(const QString& info);
    //void goToPage(/*EnumPage*/int);



private slots:
    void handleInputCard();

    void handleZero();
    void handleOne();
    void handleTwo();
    void handleTree();
    void handleFour();
    void handleFive();
    void handleSix();
    void handleSeven();
    void handleEight();
    void handleNine();
    void handleMinus();
    void handlePlus();

    void handleDelete();
    void handleEnter();
    void handleNothing();

    void handleButtonL1();
    void handleButtonL2();
    void handleButtonL3();
    void handleButtonL4();
    void handleButtonR1();
    void handleButtonR2();
    void handleButtonR3();
    void handleButtonR4();

private:
    void timerEvent(QTimerEvent *event);
    int state;
    Ui::MainWindow *ui;
    void attachListeners();
    //void changeAvailable();
};
#endif // MAINWINDOW_H
