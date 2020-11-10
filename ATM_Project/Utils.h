#ifndef UTILS_H
#define UTILS_H

enum ScreenButton {
    L1,L2,L3,L4,
    R1,R2,R3,R4
};
enum PinButton {
    B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,
    ENTER, CORRECTION, CANCEL
};

enum InputField{
    CashSum, GameAccountID, GameSum, CharitySum, PhoneNum, PhoneSum, TransactionCard, TransactionSum
};

// widget pages indexes
// 0 welcome
// 1 PIN
// 2 Menu
// 3 balance
// 4 transaction data
// 5 phone data
// 6 get cash
// 7 select charity
// 8 charity data
// 9 select game
// 10 game data
enum ScreenPage{
    Welcome, EnterPIN, Menu, Balance,
    TransactionData, PhoneData, GetCash, SelectCharity,
    CharityData, SelectGame, GameData
};


#endif // UTILS_H
