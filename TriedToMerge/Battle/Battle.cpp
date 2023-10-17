#include "Battle.h"
#include <iostream>
#include "../Entity/EntityList.h"
#include <set>
#include <cstdlib>
Battle::Battle() : myTurn(true) { setUp(); }
Battle::~Battle() {}
int Battle::getRound()
{
    return round;
}

void Battle::start()
{
    round = 0;
    while (!checkEnd())
    {
        handleTurn();
        myTurn = !myTurn;
    }
}
void Battle::handleTurn()
{
    if (myTurn)
    {
        std::cout << "It is your turn" << std::endl;
        handleMyTurn();
        // std::cout << "DEBUG:after handleMyTurn()" << std::endl;
    }
    else
    {
        std::cout << "It is enemy's turn" << std::endl;
        handleEnemyTurn();
    }
    std::cout << "-----------------round " << round << " end-----------------" << std::endl;
    round++;
    removeDead();
    // std::cout << "DEBUG: after removedead()" << std::endl;
    printTeam();
}
void Battle::handleMyTurn()
{
    for (int charactorIndex = 0; charactorIndex < myTeam.teamSize(); charactorIndex++)
    {
        Entity *currentHero = myTeam.getEntity(charactorIndex);
        std::cout << "-----------CHOOSE SKILL FOR" << currentHero->getName() << "-----------" << std::endl;
        currentHero->printEntityDetail();
        int choose;
        std::cout << "choose skill: ";
        std::cin >> choose;
        handleAttack(myTeam.getEntity(charactorIndex), choose);
        removeDead();
        std::cout << "-----------ENEMY TEAM-----------" << std::endl;
        enemyTeam.printTeam();
        // std::cout << "DEBUG:after handleAttack()" << std::endl;
    }
}
void Battle::handleEnemyTurn()
{
    for (int charactorIndex = 0; charactorIndex < enemyTeam.teamSize(); charactorIndex++)
    {
        // std::cout << "DEBUG: charactorIndex" << charactorIndex << std::endl;
        Entity *currentHero = enemyTeam.getEntity(charactorIndex);
        int choose = rand() % currentHero->getskillSize();
        // std::cout << "DEBUG:choose" << choose << std::endl;
        handleAttack(enemyTeam.getEntity(charactorIndex), choose);
        // std::cout << "DEBUG:after handleAttack()" << std::endl;
        removeDead();
    }
}
void Battle::setUp()

{
    std::vector<Entity *> myHeros{Charactor1Ptr, Charactor2Ptr, Charactor3Ptr, Charactor4Ptr, Charactor5Ptr};
    myTeam = Team();
    std::cout << "Please select your team" << std::endl;
    for (int i = 0; i < myHeros.size(); i++)
    {
        std::cout << i << ": " << myHeros[i]->getName() << std::endl;
    }
    //------------------these are for user choose charactor--------------
    // int choose;
    // std::cout << "Slot0:";
    // std::cin >> choose;
    // myTeam.setEntity(0, myHeros.at(choose));
    // std::cout << "Slot1:";
    // std::cin >> choose;
    // myTeam.setEntity(1, myHeros.at(choose));
    // std::cout << "Slot2:";
    // std::cin >> choose;
    // myTeam.setEntity(2, myHeros.at(choose));
    // std::cout << "Slot3:";
    // std::cin >> choose;
    // myTeam.setEntity(3, myHeros.at(choose));
    myTeam.setEntity(0, Charactor1Ptr);
    myTeam.setEntity(1, Charactor2Ptr);
    myTeam.setEntity(2, Charactor3Ptr);
    myTeam.setEntity(3, Charactor4Ptr);

    enemyTeam.setEntity(0, Charactor5Ptr);
    enemyTeam.setEntity(1, Charactor6Ptr);
    enemyTeam.setEntity(2, Charactor7Ptr);
    enemyTeam.setEntity(3, Charactor8Ptr);
    printTeam();
}

void Battle::handleAttack(Entity *attacker, int skillIndex)
{
    // std::cout << "DEBUG:called handleAttack()" << std::endl;
    // std::cout << "DEBUG:skillIndex" << skillIndex << std::endl;
    Skill *skill = attacker->getSkill(skillIndex);
    // std::cout << "DEBUG: getSkill()" << std::endl;
    std::set<Entity *> attackingRange = std::set<Entity *>();
    if (myTurn)
    {
        if (skill->getAttackRange() >= enemyTeam.teamSize())
        {
            for (int i; i < enemyTeam.teamSize(); i++)
                attackingRange.insert(enemyTeam.getEntity(i));
        }
        else
        {
            for (int attackNum = 0; attackNum < skill->getAttackRange(); attackNum++)
            {
                std::cout << "-----------ENEMY TEAM-----------" << std::endl;
                enemyTeam.printTeam();
                int attackChoice;
                std::cout << "Choose the " << attackNum + 1 << "th to attack";
                std::cin >> attackChoice;
                while (attackingRange.find(enemyTeam.getEntity(attackChoice)) != attackingRange.end())
                {
                    for (Entity *a : attackingRange)
                    {
                        std::cout << a << std::endl;
                    }
                    std::cout << "you cannot attack the same enemy twice";
                    std::cin >> attackChoice;
                }
                attackingRange.insert(enemyTeam.getEntity(attackChoice));
            }
        }
    }
    else
    {
        // std::cout << "DEBUG:called handleAttack() enemy" << std::endl;
        for (int attackNum = 0; attackNum < skill->getAttackRange() && attackNum < myTeam.teamSize(); attackNum++)
        {
            attackingRange.insert(myTeam.getEntity(attackNum));
        }
    }
    // std::cout << "DEBUG:after creating attackign range" << std::endl;
    for (Entity *entity : attackingRange)
    {
        int damage = attacker->getAttack() * (1 + attacker->getSkill(skillIndex)->getDamage());
        entity->takeDamage(damage);
        std::cout << entity->getName() << " takes " << damage << " damage form " << attacker->getName() << std::endl;
    }
}
void Battle::printTeam()
{
    std::cout << "-----------MY TEAM-----------" << std::endl;
    myTeam.printTeam();

    std::cout << "-----------ENEMY TEAM-----------" << std::endl;
    enemyTeam.printTeam();
}
void Battle::removeDead()
{
    for (int i = 0; i < myTeam.teamSize(); i++)
    {
        if (myTeam.getEntity(i)->ifDead())
        {
            std::cout << myTeam.getEntity(i)->getName() << " DEAD" << std::endl;
            myTeam.removeEntity(i);
            i--;
        }
    }
    for (int i = 0; i < enemyTeam.teamSize(); i++)
    {
        if (enemyTeam.getEntity(i)->ifDead())
        {
            std::cout << enemyTeam.getEntity(i)->getName() << " DEAD" << std::endl;
            enemyTeam.removeEntity(i);
            i--;
        }
    }
}
bool Battle::checkEnd()
{
    if (enemyTeam.teamSize() == 0)
    {
        win = true;
        std::cout << "You win" << std::endl;
        return true;
    }
    if (myTeam.teamSize() == 0)
    {
        win = false;
        std::cout << "You loss" << std::endl;
        return true;
    }
    return false;
}
