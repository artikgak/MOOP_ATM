#ifndef PHONESTATE_H
#define PHONESTATE_H

#include "WindowState.h"
#include "mainwindow.h"

class PhoneState : public WindowState
{
private:
    bool sumActive;   // 1 - sum, 0 - phoneNum

public:
    PhoneState(MainWindow* context): WindowState(context), sumActive(1){
        //getUi()->phoneNumField->setStyleSheet("background: #E8FAD5;");
        // memory violation access ???
    }
private:
    const QString do_screenName() override {
        return "Phone recharge";
    }

    void do_clearCurrentPage() override {
        getUi()->phoneNumField->setText("+380");
        getUi()->phoneSumField->setText("");
        getUi()->phoneError->setText("");
        getUi()->phoneCommision->setText("");
        getUi()->phoneSumField->setStyleSheet("background: #E8FAD5;"); //moved here
        getUi()->phoneNumField->setStyleSheet("");
    }

    void do_handleButtonL1() override{
        sumActive=1;
        getUi()->phoneSumField->setStyleSheet("background: #E8FAD5;");
        getUi()->phoneNumField->setStyleSheet("background: white;");
    }
    void do_handleButtonR1() override{
        handleButtonL1();
    }
    void do_handleButtonL2() override{
        sumActive=0;
        getUi()->phoneSumField->setStyleSheet("background: white;");
        getUi()->phoneNumField->setStyleSheet("background: #E8FAD5;");
    }
    void do_handleButtonR2() override{
        handleButtonL2();
    }

    void do_handleButtonL4() override{
        QString num = getUi()->phoneSumField->text();
        if(num.length() == 0){
            getUi()->transError->setText("Please enter the sum");
            return;
        }
        QString phoneNum = getUi()->phoneNumField->text();
        if(phoneNum.length()!=13){
            getUi()->phoneError->setText("Phone number must be 12 digits");
            return;
        }

        bool *ok = nullptr;
        uint sum = num.toUInt(ok);
        assert(&ok); //should always be a valid number

        PhoneResponse response = emit context->rechargePhone(sum);
        switch (response) {
        case NotEnoughMoney:
            getUi()->phoneError->setText("Not enough funds");
            return;
        case POK:
            getUi()->succFailLab->setText("Phone recharge successful\nThank You for using our bank.");
            getUi()->succFailLab->setStyleSheet("color: #269E13;");
            context->goToPage(SuccessFail);
            return;
        case PFail:
            getUi()->phoneError->setText("Error. Please try later.");
            return;
        }
    }

    void do_handleButtonR4() override{context->goToPage(Menu);}


    //CHARACTER HANDLING
    void do_enterNum(char num) override {
        if(sumActive){
        QString prev = getUi()->phoneSumField->text();
        if (prev.length()==7) return; // how many money?
        getUi()->phoneSumField->setText(prev+num);
        } else{
        QString prev = getUi()->phoneNumField->text();
        if (prev.length()==13) return; // max card len
        getUi()->phoneNumField->setText(prev+num);
        }
    }

    void do_handleButtonCorrect() override {
        assert(getUi()->phoneNumField->text().length()>=4);
        if(sumActive){
        QString prev = getUi()->phoneSumField->text();
        QString newText = prev.length() == 0 ? "" : prev.chopped(1);
        getUi()->phoneSumField->setText(newText);
        }
        else{
        QString prev = getUi()->phoneNumField->text();
        if(prev.length()>4)
        {
            getUi()->phoneNumField->setText(prev.chopped(1));
        }
        }
    }

    void do_handleButtonDelete() override {
        assert(getUi()->phoneNumField->text().length()>=4);
        sumActive ? getUi()->phoneSumField->setText("") : getUi()->phoneNumField->setText("+380");
    }

};

#endif // PHONESTATE_H
