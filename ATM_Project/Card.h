#pragma once
#define uint64 unsigned long long
class Card {
    
private:
const uint64 cardNumber;

public:
    Card(const Card&);
    Card(const uint64);
    
    Card() = delete;
    Card& operator=(const Card&) = delete;

    ~Card();

    uint64 getNumber() const;
};
