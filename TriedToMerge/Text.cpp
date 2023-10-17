#include <iostream>
#include "Text.h"
#include "GameManager.h"

void Text::keyEvent(char cha)
{
    return;
}
Text::Text(GameManager *gameManager, int _x, int _y, std::string _displayText) : Component(gameManager, _x, _y), displayText(_displayText)
{
    w = _displayText.length();
    h = 1;
}
void Text::render()
{
    _CursorService->moveCursor(x, y);
    std::cout << displayText;
}
void Text::select()
{
    return;
}
void Text::unSelect()
{
    return;
}
