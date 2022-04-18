#include <math.h>
#include "Calc.h"

//‰ñ“]
float Calc::RotateX(float x, float y, float radian)
{
    float resultX = x * cos(radian) - y * sin(radian);

    return resultX;
}
float Calc::RotateY(float x, float y, float radian)
{
    float resultY = x * sin(radian) + y * cos(radian);

    return resultY;
}
