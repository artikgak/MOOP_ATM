#pragma once
#define uint64 unsigned long long
class Card {
    
private:
uint64 cardNumber;

public:
    Card(const Card&);
    Card(const uint64);
    
    Card() = delete;
    Card& operator=(const Card&);

    ~Card() {};

    uint64 getNumber() const;
};
