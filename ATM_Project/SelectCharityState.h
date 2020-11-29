#pragma once

#include "WindowState.h"
#include "mainwindow.h"
#include "Charity.h"
#include "QString"

class SelectCharityState : public WindowState
{
private:
    std::vector<Charity> charities;
public:
    SelectCharityState(MainWindow* context, uint page) : WindowState(context)    {

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
    }


    void do_handleButtonR4() override{context->goToPage(Menu);}

    ~SelectCharityState() {
    }
};
