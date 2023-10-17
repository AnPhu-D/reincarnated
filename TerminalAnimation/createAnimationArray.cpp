#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>

using namespace std;

class image
{
private:
    string picFile;
    int file_size;
    int colorList[6] = {0, 95, 135, 175, 215, 255};
    vector<vector<vector<int>>> pixels;
    map<int, int> colorMap;
    int computeColorCode(vector<int> RGB)
    {
        // cout << RGB[0] << RGB[1] << RGB[2] << RGB[3] << endl;
        for (int color = 1; color < 4; color++)
        {
            for (int i = 0; i < 5; i++)
            {
                if (RGB[color] >= colorList[i] && RGB[color] <= colorList[i + 1])
                {
                    if ((RGB[color] - colorList[i]) < colorList[i + 1] - RGB[color])
                        RGB[color] = i;
                    else
                        RGB[color] = i + 1;
                    break;
                }
            }
        }
        return 16 + 36 * RGB[1] + 6 * RGB[2] + RGB[3];
    }

    void createAnimationArray()
    {
        vector<vector<int>> frame = vector<vector<int>>(height, vector<int>(width));
        for (int currentFrame = 0; currentFrame < frameNum; currentFrame++)
        {
            for (int h = 0; h < height; h++)
            {
                for (int rowWidth = 0; rowWidth < width; rowWidth++)
                {
                    int w = rowWidth + currentFrame * width;
                    // cout << pixels[h][w][0] << " " << pixels[h][w][1] << " " << pixels[h][w][2] << " " << pixels[h][w][3] << endl;
                    int colorHash = pixels[h][w][1] + pixels[h][w][2] * 2 + pixels[h][w][3] * 3;
                    if (colorMap.find(colorHash) != colorMap.end())
                    {
                        frame[h][rowWidth] = colorMap[colorHash];
                        continue;
                    }
                    int colorCode;
                    if (pixels[h][w][1] == 255 && pixels[h][w][2] == 255 && pixels[h][w][3] == 255)
                    {
                        colorCode = 0;
                    }
                    else
                        colorCode = computeColorCode(pixels[h][w]);
                    colorMap[colorHash] = colorCode;
                    frame[h][w] = colorCode;
                }
                // cout << endl;
            }
            animationArray.push_back(frame);
            // cout << "finish frame " << currentFrame << endl;
        }
    }
    void storeInFile()
    {
        // cout << "start storeInfile";
        string Filename = picFile.substr(0, picFile.length() - 4);
        ofstream outFS(Filename + "animationArray.h");
        outFS << "#include \"animation.h\"\nstruct " << Filename << " : public animation\n{\n\t" << Filename << "()\n\t{\n\theight = " << height << ";\n"
              << "\twidth = " << width << ";\n\tframeNum = " << frameNum << ";\n\tanimationArray =";
        outFS << "{";
        for (int currentFrame = 0; currentFrame < frameNum; currentFrame++)
        {
            outFS << "{";
            for (int h = 0; h < height; h++)
            {
                outFS << "{";
                outFS << animationArray[currentFrame][h][0];
                for (int w = 1; w < width; w++)
                {
                    outFS << ", " << animationArray[currentFrame][h][w];
                }
                outFS << "}";
                if (h != height - 1)
                    outFS << ",";
            }
            outFS << "}";
            if (currentFrame != frameNum - 1)
                outFS << ",";
        }
        outFS << "};};};";
        cout << "\nfinish storeInfile";
    }

public:
    int frameNum;
    int totalWidth;
    int width;
    int height;
    vector<vector<vector<int>>> animationArray;
    image(int _frameNum, string file) : frameNum(_frameNum), picFile(file)
    {
        ifstream inFS(picFile, ifstream::binary);
        if (!inFS.is_open())
        {
            throw runtime_error("cannot open file");
        }
        // move to file's position
        inFS.seekg(18);
        inFS.read((char *)&totalWidth, sizeof(int));
        width = totalWidth / frameNum;
        inFS.seekg(22);
        inFS.read((char *)&height, sizeof(int));
        inFS.seekg(10);
        int begin;
        inFS.read((char *)&begin, sizeof(int));
        pixels = vector<vector<vector<int>>>(height, vector<vector<int>>(totalWidth, vector<int>(4)));
        inFS.seekg(begin);
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < totalWidth; w++)
            {
                for (int color = 0; color < 4; color++)
                {
                    unsigned char pixel;
                    inFS.read((char *)&pixel, sizeof(unsigned char));
                    pixels[height - 1 - h][totalWidth - 1 - w][4 - color - 1] = (int)pixel;
                }
                // cout << (pixels[h][w][1]) << " " << (pixels[h][w][2]) << " " << (pixels[h][w][3]) << endl;
            }
        }
        animationArray = vector<vector<vector<int>>>();
        createAnimationArray();
        storeInFile();
    }
};

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "usage: <.exe> <framNum> <picture.bmp>" << endl;
        return 0;
    }
    std::ios_base::sync_with_stdio(false);
    cout << argv[1] << argv[2];
    char *frame = argv[1];
    int frameNum = atoi(frame);
    image img = image(frameNum, argv[2]);
}