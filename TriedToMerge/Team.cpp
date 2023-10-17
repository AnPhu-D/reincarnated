#include "Team.h"
#include <stdexcept>
#include <iostream>
// public:
Team::Team()
{
    entityList = std::vector<Entity *>();
}
Team::Team(std::vector<Entity *> team) : entityList(team) {}

void Team::setEntity(int index, Entity *newEntity)
{
    if (index >= 4 || index < 0)
        throw std::overflow_error("invalid index");
    entityList.at(index) = newEntity;
}
void Team::removeEntity(int index)
{
    delete entityList.at(index);
    entityList.erase(entityList.begin() + index);
}
Entity *Team::getEntity(int index)
{
    if (index >= entityList.size() || index < 0)
    {
        return entityList.at(entityList.size() - 1);
    }
    return entityList.at(index);
}

void Team::printTeam()
{
    for (int i = 0; i < entityList.size(); i++)
    {
        std::cout << "#" << i << " ";
        // entityList.at(i)->printEntity();
    }
}
int Team::teamSize()
{
    return entityList.size();
}

void Team::addEntity(Entity *entity)
{
    if (teamSize() >= 4)
    {
        return;
    }
    entityList.push_back(entity);
}