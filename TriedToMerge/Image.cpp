#include "Image.h"
Image::Image(GameManager *gameManager, int _x, int _y, const std::vector<std::vector<int>> &_ImageArray) : Component(gameManager, _x, _y)
{
    w = _ImageArray.at(0).size();
    h = _ImageArray.size();
    ImageArray.push_back(std::vector<int>());
    for (int i = 0; i < h; i++)
    {
        ImageArray.push_back(std::vector<int>());
        for (int j = 0; j < w; j++)

        {
            ImageArray.at(i).push_back(_ImageArray.at(i).at(j));
        }
    }
}
void Image::keyEvent(char cha)
{
    return;
}
void Image::render()
{
    _CursorService->moveCursor(x, y);
    for (int i = 0; i < h; i++)
    {
        _CursorService->moveCursor(x, y + i);
        for (int j = 0; j < w; j++)
        {
            if (ImageArray.at(i).at(j) == 0)
                std::cout << "\033[1C";
            else
                std::cout << "\e[48;5;" << ImageArray[i][j] << "m" << char(32) << "\e[49m";
        }
    }
}
Image::~Image()
{

    w = ImageArray.at(0).size();
    h = ImageArray.size();
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < h; j++)
        {
            ImageArray.at(i).pop_back();
        }
    }
    ImageArray.clear();
}
void Image::select() { return; }
void Image::unSelect() { return; }
