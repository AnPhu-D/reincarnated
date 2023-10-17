#ifndef __WALLET_H__
#define __WALLET_H__

class Wallet {
 public:
  Wallet(unsigned _maxBalance);

  unsigned getBalance() const;
  void setBalance(unsigned _balance);

  void addBalance(unsigned balanceToAdd);
  void removeBalance(unsigned balanceToRemove);

 private:
  unsigned balance = 0;
  unsigned maxBalance;
};

#endif