
#ifndef BUTTON
#define BUTTON
#include "Component.h"
#include "GameManager.h"
#include <string>

class Button : public Component
{
private:
    std::string displayText;
    bool selected;

public:
    ~Button()
    {
        return;
    }
    Button(GameManager *, int, int, std::string, bool);
    void keyEvent(char cha) override;
    void render() override;
    void select() override;
    void unSelect() override;
    std::string getDisplayText();
};

#endif // !BUTTON
