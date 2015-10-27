#ifndef CV_H
#define CV_H

#include <stdint.h>

struct Line
{
    uint8_t exist;
    int32_t angle;
    int32_t distance;
    int32_t horizontal;
};
struct sBlue
{
    bool exist;
    int x;
    int y;
};

struct Circle
{
    bool exist;
    float x;
    float y;
    uint8_t number;
    int maxRadius;
};
struct Basket
{
    float x;
    float y;
    float angle;
    float ballX;
    float ballY;
};

namespace Grid
{
    enum Color
    {
        Red,
        Yellow,
        NoColor
    };
}
typedef struct
{
    bool exist;
    uint8_t number;
    Grid::Color color;
    int x;
    int y;
}sGrid;
class CVision
{
public:
static Circle scanCircle();
static Line scanLine();
static Basket scanBasket();
static void init();
};

#endif // CV_H
