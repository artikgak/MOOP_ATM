#pragma once
#include "WindowState.h"
#include "mainwindow.h"

#include <QMessageBox>

class WithdrawState : public WindowState {

    const QString screenName() override {
        return "Withdraw funds";
    }

    void clearCurrentPage() override {
        getUi()->cashSumField->setText("");
        getUi()->withdrawErrorMsg->setText("");
    }

    void handleButtonR4() override {
        context->goToPage(Menu);
    }

    void handleButtonL4() override {
        QString num = getUi()->cashSumField->text();
        if(num.length() == 0) return;

        bool *ok = nullptr;
        uint sum = num.toUInt(ok);
        assert(&ok); //should always be a valid number

        WithdrawResponse response = emit context->withdrawMoney(sum);

        switch (response) {
        case AtmNoBills:
            context->displayAvailBankNotes();
            //getUi()->withdrawErrorMsg->setText("Доступні копюри: ");
            return;
        case UserNoMoney:
            getUi()->withdrawErrorMsg->setText("Not enough funds");
            return;
        case AtmNoMoney:
            getUi()->withdrawErrorMsg->setText("Not enough money in ATM");
            return;
        case WOK:
            QMessageBox::information(context,"Money", "Please take your bills");
            context->goToPage(Menu);
            break;
        }
    }

    //CHARACTER HANDLING
    void enterNum(char num) override {
        QString prev = getUi()->cashSumField->text();
        if (prev.length()==5) return;
        getUi()->cashSumField->setText(prev+num);
    }

    void handleButtonCorrect() override {
        QString prev = getUi()->cashSumField->text();
        QString newText = prev.length() == 0 ? "" : prev.chopped(1);
        getUi()->cashSumField->setText(newText);
    }

    void handleButtonDelete() override {
        getUi()->cashSumField->setText("");
    }

};
