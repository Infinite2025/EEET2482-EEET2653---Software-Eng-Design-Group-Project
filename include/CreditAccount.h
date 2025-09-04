#pragma once
#include <string>

class CreditAccount {
private:
    int balance; // CP balance

public:
    CreditAccount(int initial = 0);

    int getBalance() const;
    bool deposit(int usd); // 1 USD = 1 CP
    bool withdraw(int cp); // returns false if insufficient balance
    bool canAfford(int cp) const;
};