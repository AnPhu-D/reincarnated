
#ifndef BATTLESESSION
#define BATTLESESSION
#include "Component.h"
#include "GameManager.h"
#include <string>
#include <vector>

class BattleSession : public Component
{
private:
    // unsigned selectIndex = 0;
    // int chosenSkill = 0;
    // battleState currentState = battleState::choosingSkill;
    // std::vector<bool> attackList;
    // void handleEnemyTurn();
    // void handleAttack(Entity *, int);
    // void removeDead();

public:
    ~BattleSession();
    BattleSession(Party *, Party *);
    int getRound();
    bool getWin();
    int getCurrentEntity());
    vector<Entity *> getTurnOrder();
    Party *getPartyA();
    Party *getPartyB();
    bool getGameOver();
    void Run();
};

#endif // !BattleSession
