QT       += core gui sql testlib multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 sdk_no_version_check

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ATM.cpp \
    WindowState.cpp \
    main.cpp \
    mainwindow.cpp \
    DataBase.cpp \
    testfront.cpp

HEADERS += \
    ATM.h \
    AdminState.h \
    BalanceState.h \
    Charity.h \
    Cheque.h \
    IdleState.h \
    MenuState.h \
    PhoneState.h \
    PinState.h \
    SelectCharityState.h \
    SuccessFailState.h \
    TransferState.h \
    Utils.h \
    WindowState.h \
    WithdrawState.h \
    mainwindow.h \
    DataBase.h \
    testfront.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qtResources.qrc

#DISTFILES += \
#    bnkNote.txt \
#    db.sqlite

OTHER_FILES += \
   bnkNote.txt \
   db.sqlite
