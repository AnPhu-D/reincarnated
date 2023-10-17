#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <string>
#include <map>

#include "entity.h"
#include "wallet.h"

class Player {
 public:
  // Constructor
  Player();

  // Accessors
  Wallet* getGoldWallet() const { return goldWallet; }
  Wallet* getGemWallet() const { return gemWallet; }

 private:
  // Members
  Wallet* goldWallet = new Wallet(10000);
  Wallet* gemWallet = new Wallet(10000);

  std::map<std::string, Entity> heroes;
};

#endif