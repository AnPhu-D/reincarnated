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
    void removeEntity(int);
    void printTeam();
    std::string toString(); // return a string of the team in the printing format
    int teamSize();
    void addEntity(Entity *);

private:
    std::vector<Entity *> entityList;
};
#endif // !TEAM
