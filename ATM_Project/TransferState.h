#ifndef TRANSFERSTATE_H
#define TRANSFERSTATE_H
#include "WindowState.h"
#include "mainwindow.h"

class TransferState : public WindowState
{
private:
    bool sumActive;   // 1 - sum, 0 - target card

public:
    TransferState():sumActive(1){
      //  getUi()->transactionSumField->setStyleSheet("background: #E8FAD5;");
        // memory violation access ???
    }
<<<<<<< Updated upstream
<<<<<<< Updated upstream
<<<<<<< Updated upstream

    const QString screenName() override {
        return "Переказ грошей";
=======
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
private:
    const QString do_screenName() override {
        return "Money transfer";
>>>>>>> Stashed changes
    }

    void do_clearCurrentPage() override {
        getUi()->transactionSumField->setText("");
        getUi()->targetCardField->setText("");
        getUi()->transferCommision->setText("");
        getUi()->transError->setText("");
        getUi()->transactionSumField->setStyleSheet("background: #E8FAD5;"); //moved here
        getUi()->targetCardField->setStyleSheet("");
    }

    void do_handleButtonL1() override{
        sumActive=1;
        getUi()->transactionSumField->setStyleSheet("background: #E8FAD5;");
        getUi()->targetCardField->setStyleSheet("background: white;");
    }
    void do_handleButtonR1() override{
        handleButtonL1();
    }
    void do_handleButtonL2() override{
        sumActive=0;
        getUi()->transactionSumField->setStyleSheet("background: white;");
        getUi()->targetCardField->setStyleSheet("background: #E8FAD5;");
    }
    void do_handleButtonR2() override{
        handleButtonL2();
    }

    void do_handleButtonL4() override{


        QString num = getUi()->transactionSumField->text();
        if(num.length() == 0){
            getUi()->transError->setText("Порожня сума");
            return;
        }
        QString targetCard = getUi()->targetCardField->text();
        if(targetCard.length()!=8){
            getUi()->transError->setText("Номер картки має 8 цифр");
            return;  // card len
        }

        bool *ok = nullptr;
        uint sum = num.toUInt(ok);
        assert(&ok); //should always be a valid number

        TransferResponse response = emit context->transferMoney(sum, targetCard.toStdString());

        switch (response) {
        case NotEnoughMonet:
            getUi()->transError->setText("Недостатньо грошей на рахунку");
            return;
        case TARGETCARDNOTFOUND:
            getUi()->transError->setText("Недійсний номер катки отримувача");
            return;
        case FAIL:
            getUi()->succFailLab->setText("Помилка переказу\nСервер перевантажений,\nспробуйте пізінше.");
            getUi()->succFailLab->setStyleSheet("color: #E64B09;");
            context->goToPage(SuccessFail);
            return;
        case TOK:
            getUi()->succFailLab->setText("Переказ успішний\nДякуємо, що користуєтесь нашим банком.");
            getUi()->succFailLab->setStyleSheet("color: #269E13;");
            context->goToPage(SuccessFail);
            return;
        }
    }

    void do_handleButtonR4() override{context->goToPage(Menu);}


    //CHARACTER HANDLING
    void do_enterNum(char num) override {
        if(sumActive){
        QString prev = getUi()->transactionSumField->text();
        if (prev.length()==7) return; // how many money?
        getUi()->transactionSumField->setText(prev+num);
        } else{
        QString prev = getUi()->targetCardField->text();
        if (prev.length()==8) return; // max card len
        getUi()->targetCardField->setText(prev+num);
        }
    }

    void do_handleButtonCorrect() override {
        if(sumActive){
        QString prev = getUi()->transactionSumField->text();
        QString newText = prev.length() == 0 ? "" : prev.chopped(1);
        getUi()->transactionSumField->setText(newText);
        }
        else{
        QString prev = getUi()->targetCardField->text();
        QString newText = prev.length() == 0 ? "" : prev.chopped(1);
        getUi()->targetCardField->setText(newText);
        }
    }

    void do_handleButtonDelete() override {
        sumActive ? getUi()->transactionSumField->setText("") : getUi()->targetCardField->setText("");
    }

};

#endif // TRANSFERSTATE_H
