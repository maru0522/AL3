#pragma once

#define PI 3.14159265358979323846f
#define RADIANS(deg) (((deg)/360.0f)*2*PI)
#define FPS(sec) (sec * 50.0f)

class Calc
{
public:
    //‰ñ“]
    static float RotateX(float x, float y, float radian);
    static float RotateY(float x, float y, float radian);
};