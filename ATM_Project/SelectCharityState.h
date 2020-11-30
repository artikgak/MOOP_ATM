#pragma once

#include "WindowState.h"
#include "mainwindow.h"
#include "Charity.h"
#include "QString"
#include "QDebug"
#include <QMessageBox>


class SelectCharityState : public WindowState
{
private:
    std::vector<Charity> charities;
    uint select;
public:
    SelectCharityState(MainWindow* context, uint page) : WindowState(context)    {

        do_handleButtonL1();

        charities = (emit context->getCharities(page));

        for (uint i = 0; i < charities.size(); i++){
            const QString name = QString::fromStdString(charities[i].name);
            switch (i){
            case 0:
                getUi()->charity1->setText(name);
                break;
            case 1:
                getUi()->charity2->setText(name);
                break;
            case 2:
                getUi()->charity3->setText(name);
                break;
            case 3:
                getUi()->charity4->setText(name);
                break;
            case 4:
                getUi()->charity5->setText(name);
                break;
            default:
                getUi()->charity6->setText(name);
                break;
            }
        }

    }

    const QString do_screenName() override {
        return "Select Charity";
    }

    void do_clearCurrentPage() override {
        getUi()->charity1->setText("");
        getUi()->charity2->setText("");
        getUi()->charity3->setText("");
        getUi()->charity4->setText("");
        getUi()->charity5->setText("");
        getUi()->charity6->setText("");
        getUi()->charitySumField->setText("");
        resetStyle();
    }

    void do_handleButtonL1() override {
        resetStyle();
        getUi()->charity1->setStyleSheet("background: #FFF2A1;"); //moved here
        select = 0;
    }
    void do_handleButtonL2() override {
        resetStyle();
        getUi()->charity2->setStyleSheet("background: #FFF2A1;"); //moved here
        select = 1;
    }
    void do_handleButtonL3() override {
        resetStyle();
        getUi()->charity3->setStyleSheet("background: #FFF2A1;"); //moved here
        select = 2;
    }

    void do_handleButtonR1() override {
        resetStyle();
        getUi()->charity4->setStyleSheet("background: #FFF2A1;"); //moved here
        select = 3;
    }

    void do_handleButtonR2() override {
        resetStyle();
        getUi()->charity5->setStyleSheet("background: #FFF2A1;"); //moved here
        select = 4;
    }

    void do_handleButtonR3() override {
        resetStyle();
        getUi()->charity6->setStyleSheet("background: #FFF2A1;"); //moved here
        select = 5;
    }

    void do_handleButtonR4() override{context->goToPage(Menu);}
    void do_handleButtonL4() override{
        QString num = getUi()->charitySumField->text();
        if(num.length() == 0)
            return;


        bool *ok = nullptr;
        uint sum = num.toUInt(ok);
        assert(&ok);


        TransferResponse isPaymentOk = emit context->payCharity(charities[select].id-1, sum);

        switch (isPaymentOk)
        {
        case NotEnoughMonet:
            getUi()->succFailLab->setText("Not enough money on your balance.");
            getUi()->succFailLab->setStyleSheet("color: #fa8072;");
            getUi()->printCheckLabel->setText("");
            context->goToPage(SuccessFail);
            break;
        case TOK:
            getUi()->succFailLab->setText("Donation successful\nThank You for using our bank.");
            getUi()->succFailLab->setStyleSheet("color: #269E13;");
            context->goToPage(SuccessFail);
            break;
        default:
            getUi()->succFailLab->setText("Donation is not available now. Try later");
            getUi()->succFailLab->setStyleSheet("color: #fa8072;");
            context->goToPage(SuccessFail);
            break;
        }

    }

    void resetStyle() {
        getUi()->charity1->setStyleSheet(""); //moved here
        getUi()->charity2->setStyleSheet(""); //moved here
        getUi()->charity3->setStyleSheet(""); //moved here
        getUi()->charity4->setStyleSheet(""); //moved here
        getUi()->charity5->setStyleSheet(""); //moved here
        getUi()->charity6->setStyleSheet(""); //moved here
    }

    //CHARACTER HANDLING
    void do_enterNum(char num) override {
        QString prev = getUi()->charitySumField->text();
        if (prev.length()==5) return;
        qDebug() << "new text: " << prev+num;
        getUi()->charitySumField->setText(prev+num);
    }

    void do_handleButtonCorrect() override {
        QString prev = getUi()->charitySumField->text();
        QString newText = prev.length() == 0 ? "" : prev.chopped(1);
        getUi()->charitySumField->setText(newText);
    }

    void do_handleButtonDelete() override {
        getUi()->charitySumField->setText("");
    }

    ~SelectCharityState() {
    }
};
