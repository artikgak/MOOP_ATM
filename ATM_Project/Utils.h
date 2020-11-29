#ifndef UTILS_H
#define UTILS_H

enum Button {
    L1,L2,L3,L4,
    R1,R2,R3,R4,
    B0,B1,B2,B3,B4,B5,B6,B7,B8,B9,
    ENTER, CORRECTION, CANCEL
};

enum ATMState {
    Idle, S1, S2, S3, Fin, Mntnc,
};

enum InputField{
    CashSum, GameAccountID, GameSum, CharitySum, PhoneNum, PhoneSum, TransactionCard, TransactionSum
};

enum TransferResponse{
    NotEnoughMonet, TOK, FAIL, TARGETCARDNOTFOUND
};

enum WithdrawResponse {
    AtmNoMoney, UserNoMoney, AtmNoBills, WOK
};

enum PhoneResponse{
    NotEnoughMoney, POK, PFail
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
    CharityData, SelectGame, GameData, SuccessFail, Admin
};


#endif // UTILS_H
