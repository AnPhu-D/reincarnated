#include <iostream>
#include "BattleSession.h"
#include "GameManager.h"

void BattleSession::keyEvent(char cha)
{
    if (cha == 65) // up
        selectIndex--;
    else if (cha == 66) // down
        selectIndex++;
    else if (cha == 10)
    {
        if (currentState == battleState::EnemyTurn)
        {
            handleEnemyTurn();
        }
        else if (currentState == battleState::choosingSkill)
        {

            chosenSkill = selectIndex % gameManager->myTeam->getEntity(currentEntity)->getskillSize();
            attackList = std::vector<bool>();
            if (gameManager->enemyTeam->teamSize() <= gameManager->myTeam->getEntity(currentEntity)->getSkill(chosenSkill)->getAttackRange())
            {
                for (int i = 0; i < gameManager->enemyTeam->teamSize(); i++)
                {
                    attackList.push_back(true);
                }
                currentState = battleState::attacking;
                handleAttack(gameManager->myTeam->getEntity(currentEntity), chosenSkill);
            }
            else
            {
                currentState = battleState::chossingAttack;
                for (int i = 0; i < gameManager->enemyTeam->teamSize(); i++)
                {
                    attackList.push_back(false);
                }
            }
        }
        else if (currentState == battleState::chossingAttack)
        {
            if (attackList.at(selectIndex % gameManager->enemyTeam->teamSize()))
            {
                attackList.at(selectIndex % gameManager->enemyTeam->teamSize()) = false;
            }
            else
            {
                attackList.at(selectIndex % gameManager->enemyTeam->teamSize()) = true;
            }
            int count = 0;
            for (bool i : attackList)
            {
                if (i)
                    count++;
            }
            if (count >= gameManager->myTeam->getEntity(currentEntity)->getSkill(chosenSkill)->getAttackRange())
            {
                currentState = battleState::attacking;
                handleAttack(gameManager->myTeam->getEntity(currentEntity), chosenSkill);
            }
        }
    }
}
BattleSession::BattleSession(GameManager *gameManager) : Component(gameManager, 2, 2)
{
    w = 117;
    h = 17;
    round = 0;
    currentEntity = battleState::choosingSkill;
}
void BattleSession::render()
{
    if (checkEnd())

    {
        gameManager->ScreenNavigate("win");
        return;
    }
    _CursorService->moveCursor(58, 4);
    if (currentState != battleState::EnemyTurn)
    {
        std::cout << "---YOUR TURN---";
    }
    else
        std::cout << "---ENEMY TURN---";
    _CursorService->moveCursor(58, 5);
    std::cout << "ROUND: " << round + 1;

    _CursorService->moveCursor(30, 8);
    std::cout << "-MY TEAM-";

    for (int i = 0; i < 4; i++)
    {
        _CursorService->moveCursor(40, 10 + i);
        for (int j = 0; j < 20; j++)
        {
            std::cout << " ";
        }
    }
    for (int i = 0; i < gameManager->myTeam->teamSize(); i++)
    {
        if (currentEntity == i && currentState != battleState::EnemyTurn)
        {
            for (int j = 0; j < 4; j++)
            {
                _CursorService->moveCursor(5, 18 + j);
                for (int x = 0; x < 113; x++)
                {
                    std::cout << " ";
                }
            }
            for (int j = 0; j < gameManager->myTeam->getEntity(i)->getskillSize(); j++)
            {
                _CursorService->moveCursor(27, 18 + j);
                if (currentState == battleState::choosingSkill)
                {
                    if (j == selectIndex % gameManager->myTeam->getEntity(currentEntity)->getskillSize())
                        _HighlightService->startHighlightColor("Green");
                }
                else if (currentState == battleState::chossingAttack)
                    if (j == chosenSkill)
                        _HighlightService->startHighlightColor("Red");
                gameManager->myTeam->getEntity(i)->skillList.at(j)->print();
                _HighlightService->endHighlightColor();
            }
            _HighlightService->startHighlightColor("Blue");
        }
        _CursorService->moveCursor(27, 10 + i);
        gameManager->myTeam->getEntity(i)->printEntity();
        _HighlightService->endHighlightColor();
    }

    _CursorService->moveCursor(80, 8);
    std::cout << "-ENEMY TEAM-";
    for (int i = 0; i < 4; i++)
    {
        _CursorService->moveCursor(80, 10 + i);
        for (int j = 0; j < 20; j++)
        {
            std::cout << " ";
        }
    }
    for (int i = 0; i < gameManager->enemyTeam->teamSize(); i++)
    {
        _CursorService->moveCursor(80, 10 + i);
        if (currentEntity == i && currentState == battleState::EnemyTurn)
            _HighlightService->startHighlightColor("Blue");
        else if (i == (selectIndex % gameManager->enemyTeam->teamSize()) && currentState == battleState::chossingAttack)
            _HighlightService->startHighlightColor("Yellow");
        if (i < attackList.size() and attackList.at(i) && currentState == battleState::chossingAttack)
            _HighlightService->startHighlightColor("Red");
        gameManager->enemyTeam->getEntity(i)->printEntity();
        _HighlightService->endHighlightColor();
    }
}
void BattleSession::select()
{
    return;
}
void BattleSession::unSelect()
{
    return;
}
void BattleSession::start()
{
    return;
}
void BattleSession::handleTurn()
{
    return;
}
void BattleSession::handleMyTurn()
{
    // for (int charactorIndex = 0; charactorIndex < myTeam.teamSize(); charactorIndex++)
    // {
    //     Entity *currentHero = myTeam.getEntity(charactorIndex);
    //     std::cout << "-----------CHOOSE SKILL FOR" << currentHero->getName() << "-----------" << std::endl;
    //     currentHero->printEntityDetail();
    //     int choose;
    //     std::cout << "choose skill: ";
    //     std::cin >> choose;
    //     handleAttack(myTeam.getEntity(charactorIndex), choose);
    //     removeDead();
    //     std::cout << "-----------ENEMY TEAM-----------" << std::endl;
    //     enemyTeam->printTeam();
    //     // std::cout << "DEBUG:after handleAttack()" << std::endl;
    // }
}
void BattleSession::handleEnemyTurn()
{
    int choose = rand() % gameManager->enemyTeam->getEntity(currentEntity)->getskillSize();
    handleAttack(gameManager->enemyTeam->getEntity(currentEntity), choose);
    attackList = std::vector<bool>();
    for (int i = 0; i < gameManager->myTeam->teamSize(); i++)
    {
        attackList.push_back(false);
    }
    for (int i = 0; i < gameManager->enemyTeam->getEntity(currentEntity)->getSkill(choose)->getAttackRange() and i < gameManager->myTeam->teamSize(); i++)
    {
        attackList.at(i) = true;
    }
    removeDead();
}

void BattleSession::handleAttack(Entity *attacker, int skillIndex)
{

    Skill *skill = attacker->getSkill(skillIndex);
    for (int i = 0; i < attackList.size(); i++)
    {
        if (attackList.at(i))
        {
            int damage = attacker->getAttack() * (1 + attacker->getSkill(skillIndex)->getDamage());

            if (currentState != battleState::EnemyTurn)
            {
                gameManager->enemyTeam->getEntity(i)->takeDamage(damage);
            }
            else
            {
                gameManager->myTeam->getEntity(i)->takeDamage(damage);
            }
        }
    }
    removeDead();
    render();
    currentEntity++;
    if (currentState != battleState::EnemyTurn)
    {
        if (currentEntity >= gameManager->myTeam->teamSize())
        {
            currentEntity = 0;
            currentState = battleState::EnemyTurn;
        }
        else
        {

            currentState = battleState::choosingSkill;
        }
    }
    else
    {
        if (currentEntity >= gameManager->enemyTeam->teamSize())
        {
            currentEntity = 0;
            currentState = battleState::choosingSkill;
            for (int j = 0; j < 4; j++)
            {
                _CursorService->moveCursor(5, 18 + j);
                for (int x = 0; x < 113; x++)
                {
                    std::cout << " ";
                }
            }
            round++;
        }
    }
}

void BattleSession::removeDead()
{
    for (int i = 0; i < gameManager->myTeam->teamSize(); i++)
    {
        if (gameManager->myTeam->getEntity(i)->ifDead())
        {
            gameManager->myTeam->removeEntity(i);
            i--;
        }
    }
    for (int i = 0; i < gameManager->enemyTeam->teamSize(); i++)
    {
        if (gameManager->enemyTeam->getEntity(i)->ifDead())
        {
            gameManager->enemyTeam->removeEntity(i);
            i--;
        }
    }
    if (checkEnd())
    {
        if (win)
        {
            for (int i = 0; i < 18; i++)
            {
                _CursorService->moveCursor(2, 2 + i);
                for (int j = 0; j < 55; j++)
                {
                    std::cout << " ";
                }
            }
            gameManager->ScreenNavigate("win");
        }
        else
            gameManager->ScreenNavigate("lose");
    }
}
bool BattleSession::checkEnd()
{
    if (gameManager->enemyTeam->teamSize() == 0)
    {
        win = true;
        return true;
    }
    if (gameManager->myTeam->teamSize() == 0)
    {
        win = false;
        return true;
    }
    return false;
}
