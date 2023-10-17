#ifndef ANIMATION
#define ANIMATION
#include <vector>
using std::vector;

struct animation
{
    int height;
    int width;
    int frameNum;
    vector<vector<vector<int>>> animationArray;
};
#endif