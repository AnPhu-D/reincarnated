#include "Team.h"
#include <stdexcept>
#include <iostream>
// public:
Team::Team()
{
    entityList = std::vector<Entity *>(4);
}
Team::Team(std::vector<Entity *> team) : entityList(team) {}
Team::~Team() {}
void Team::setEntity(int index, Entity *newEntity)
{
    if (index >= 4 || index < 0)
        throw std::overflow_error("invalid index");
    entityList.at(index) = newEntity;
}
void Team::removeEntity(int index)
{
    entityList.erase(entityList.begin() + index);
    // for (int i = index; i < entityList.size(); i++)
    // {
    //     if (i < entityList.size() - 1)
    //         entityList.at(index) = entityList.at(index + 1);
    // }
    // entityList.pop_back();
}
Entity *Team::getEntity(int index)
{
    if (index >= entityList.size() || index < 0)
    {
        // std::cout << "index:" << index << std::endl;
        // std::cout << "size:" << entityList.size() << std::endl;
        throw std::overflow_error("invalid index");
    }
    return entityList.at(index);
}

void Team::printTeam()
{
    for (int i = 0; i < entityList.size(); i++)
    {
        std::cout << "#" << i << std::endl;
        entityList.at(i)->printEntity();
        std::cout << std::endl;
    }
}
int Team::teamSize()
{
    return entityList.size();
}
