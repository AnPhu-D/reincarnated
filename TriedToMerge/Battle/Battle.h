#ifndef BATTLE
#define BATTLE
#include "../Team/Team.h"

class Battle
{
private:
    Team myTeam;
    Team enemyTeam;
    int round;
    bool myTurn;
    bool win;

public:
    Battle();
    ~Battle();
    int getRound();
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
#endif // !BATTLE
