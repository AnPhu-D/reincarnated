#ifndef COMPONENT
#define COMPONENT

#include <iostream>
#include <vector>
#include "services.h"
#include "frameVertex.h"
#include "textgui_constants.h"

using Services::_CursorServiceHandle;
using Services::_HighlightServiceHandle;
using Services::_LineDrawServiceHandle;

class GameManager;

class Component
{
public:
    CursorService *_CursorService = _CursorServiceHandle;
    LineDrawService *_LineDrawService = _LineDrawServiceHandle;
    HighlightService *_HighlightService = _HighlightServiceHandle;

    unsigned x, y, w, h;
    GameManager *gameManager;
    Component(GameManager *_gameManager, int _x, int _y) : gameManager(_gameManager), x(_x), y(_y){};
    virtual void render() = 0;
    virtual void keyEvent(char) = 0;
    virtual void select() = 0;
    virtual void unSelect() = 0;
    virtual ~Component(){};
    void removeFromScreen()
    {
        for (int i = 0; i < h; i++)
        {
            _CursorService->moveCursor(x, y + i);
            for (int j = 0; j < w; j++)
            {
                std::cout << " ";
            }
        }
    }
};

#endif // !COMPONENT