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

private slots:
    void handleInputCard();
    void handleEjectCard();
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
    void handleBack();

private:
    int state;
    Ui::MainWindow *ui;
    void attachListeners();
    void changeAvailable();
};
#endif // MAINWINDOW_H
