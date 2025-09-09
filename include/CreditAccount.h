#ifndef CREDITACCOUNT_H
#define CREDITACCOUNT_H
#pragma once

class CreditAccount {
private:
int balance;

public:
CreditAccount(int initial = 0);
int getBalance() const;
bool deposit(int usd);
bool withdraw(int cp);
bool canAfford(int cp) const;
};

#endif