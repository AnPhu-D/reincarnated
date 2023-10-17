#ifndef TEAM
#define TEAM
#include "../Entity/Entity.h"
#include <vector>
class Team
{
public:
    Team(std::vector<Entity *>);
    Team();
    ~Team();
    Entity *getEntity(int);
    void setEntity(int, Entity *);
    void removeEntity(int);
    void printTeam();
    int teamSize();

private:
    std::vector<Entity *> entityList;
};
#endif // !TEAM
