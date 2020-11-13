#pragma once

#include <string>

class Card {
    
private:
std::string cardNumber;

public:
    Card(const Card&);
    Card(const std::string&);
    
    Card() = delete;
    Card& operator=(const Card&);

    ~Card() {};

    std::string getPin() const;
    std::string getNumber() const;
};
