#ifndef SELECT_TEAM
#define SELECT_TEAM
#include "Component.h"
#include "GameManager.h"
#include <string>
#include "Team.h"
#include <vector>

class SelectTeam : public Component
{
private:
    std::vector<bool> selectArray;
    void printHero(int);
    int countSelected();

public:
    ~SelectTeam() { return; }
    SelectTeam(GameManager *, int, int);
    void keyEvent(char cha) override;
    void render() override;
    void select() override;
    void unSelect() override;
};

#endif // !SelectTeam
