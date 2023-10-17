
#ifndef TEXT
#define TEXT
#include "Component.h"
#include "GameManager.h"
#include <string>

class Text : public Component
{
private:
    std::string displayText;

public:
    ~Text() { return; }
    Text(GameManager *, int, int, std::string);
    void keyEvent(char cha) override;
    void render() override;
    void select() override;
    void unSelect() override;
};

#endif // !Text
