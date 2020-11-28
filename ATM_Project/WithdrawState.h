#pragma once
#include "WindowState.h"
#include "mainwindow.h"

#include <QMessageBox>

class WithdrawState : public WindowState {

<<<<<<< Updated upstream
<<<<<<< Updated upstream
    const QString screenName() override {
        return "Зняти гроші";
=======
=======
>>>>>>> Stashed changes
private:
    const QString do_screenName() override {
        return "Withdraw funds";
>>>>>>> Stashed changes
    }

    void do_clearCurrentPage() override {
        getUi()->cashSumField->setText("");
        getUi()->withdrawErrorMsg->setText("");
    }

    void do_handleButtonR4() override {
        context->goToPage(Menu);
    }

    void do_handleButtonL4() override {
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
            getUi()->withdrawErrorMsg->setText("Недостатньо грошей у користувача");
            return;
        case AtmNoMoney:
            getUi()->withdrawErrorMsg->setText("Недостатньо грошей у банкоматі");
            return;
        case WOK:
            QMessageBox::information(context,"Money", "Please take your bills");
            context->goToPage(Menu);
            break;
        }
    }

    //CHARACTER HANDLING
    void do_enterNum(char num) override {
        QString prev = getUi()->cashSumField->text();
        if (prev.length()==5) return;
        getUi()->cashSumField->setText(prev+num);
    }

    void do_handleButtonCorrect() override {
        QString prev = getUi()->cashSumField->text();
        QString newText = prev.length() == 0 ? "" : prev.chopped(1);
        getUi()->cashSumField->setText(newText);
    }

    void do_handleButtonDelete() override {
        getUi()->cashSumField->setText("");
    }

};
