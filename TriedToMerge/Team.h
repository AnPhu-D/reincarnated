#ifndef TEAM
#define TEAM
#include "../Entity/Entity.h"
#include <vector>
class Team
{
public:
    Team(std::vector<Entity *>);
    Team();
    Entity *getEntity(int);
    void setEntity(int, Entity *);
    void removeEntity(int);
    void printTeam();
    int teamSize();
    void addEntity(Entity *);
    std::vector<Entity *> entityList;

private:
};
#endif // !TEAM
