
#ifndef BATTLESESSION
#define BATTLESESSION
#include "Component.h"
#include "GameManager.h"
#include <string>
#include <vector>

enum battleState
{
    choosingSkill,
    chossingAttack,
    EnemyTurn,
    attacking
};
class BattleSession : public Component
{
private:
    int round;
    bool win;
    int currentEntity = 0;
    unsigned selectIndex = 0;
    int chosenSkill = 0;
    battleState currentState = battleState::choosingSkill;
    std::vector<bool> attackList;

public:
    ~BattleSession() override { return; }
    BattleSession(GameManager *);
    void keyEvent(char cha) override;
    void render() override;
    void select() override;
    void unSelect() override;
    void start();
    void handleMyTurn();
    void handleEnemyTurn();
    void setUp();
    void handleAttack(Entity *, int);
    void printTeam();
    void handleTurn();
    void removeDead();
    bool checkEnd();
};

#endif // !BattleSession
