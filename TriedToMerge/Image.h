#ifndef IMAGE
#define IMAGE
#include <vector>
#include "Component.h"
#include "GameManager.h"
#include <string>

class Image : public Component
{
private:
    std::vector<std::vector<int>> ImageArray;

public:
    ~Image();
    Image(GameManager *, int, int, const std::vector<std::vector<int>> &);
    void keyEvent(char cha) override;
    void render() override;
    void select() override;
    void unSelect() override;
};
#endif