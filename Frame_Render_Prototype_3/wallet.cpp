#include "wallet.h"

Wallet::Wallet(unsigned _maxBalance) {
  maxBalance = _maxBalance;
}

unsigned Wallet::getBalance() const {
  return balance;
}

void Wallet::setBalance(unsigned _balance) {
  balance = _balance;
}

void Wallet::addBalance(unsigned balanceToAdd) {
  balance += balanceToAdd;
  if (balance > maxBalance) {
    balance = maxBalance;
  }
}

void Wallet::removeBalance(unsigned balanceToRemove) {
  if (balanceToRemove >= balance) {
    balance = 0;
  } else {
    balance -= balanceToRemove;
  }
}