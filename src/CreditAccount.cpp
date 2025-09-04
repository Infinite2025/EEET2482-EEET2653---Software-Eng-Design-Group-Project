#include "CreditAccount.h"

CreditAccount::CreditAccount(int initial) : balance(initial) {}

int CreditAccount::getBalance() const {
    return balance;
}

bool CreditAccount::deposit(int usd) {
    if (usd <= 0) return false;
    balance += usd;
    return true;
}

bool CreditAccount::withdraw(int cp) {
    if (cp <= 0 || cp > balance) return false;
    balance -= cp;
    return true;
}

bool CreditAccount::canAfford(int cp) const {
    return cp >= 0 && balance >= cp;
}