#include <iostream>
#include "Button.h"
#include "GameManager.h"

void Button::keyEvent(char cha)
{
    if (!selected)
        return;
    // std::cout << "\033[" << 10 << ";" << 70 << "H";
    // std::cout << (int)cha;
    if (cha == 10)
    {
        // std::cout << "\033[" << 10 << ";" << 70 << "H";
        // std::cout << "key press" << cha;
        gameManager->ScreenNavigate(displayText);
        selected = false;
    }
}
Button::Button(GameManager *gameManager, int _x, int _y, std::string _displayText, bool _selected = false) : Component(gameManager, _x, _y), displayText(_displayText), selected(_selected)
{
    w = _displayText.length() + 2;
    h = 3;
}
void Button::render()
{
    _LineDrawService->drawRect(displayText.length(), 3, x, y);
    _CursorService->moveCursor(x + 1, y + 1);
    if (selected)
    {
        _HighlightService->startHighlightColor("Cyan");
    }
    std::cout << displayText;
    _HighlightService->endHighlightColor();
}
void Button::select()
{
    selected = true;
}
void Button::unSelect()
{
    selected = false;
}
