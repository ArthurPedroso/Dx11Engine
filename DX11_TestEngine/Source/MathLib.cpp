#include "MathLib.h"

float MathLib::VecDistance(Vec2D _vecA, Vec2D _vecB)
{
    return sqrtf(((_vecB.x - _vecA.x) * (_vecB.x - _vecA.x)) + ((_vecB.y - _vecA.y) * (_vecB.y - _vecA.y)));
}

Vec2D MathLib::VecRotate(Vec2D _toRotate, float _radians)
{
    return Vec2D((_toRotate.x * cosf(_radians)) - (_toRotate.y * sinf(_radians)), (_toRotate.x * sinf(_radians)) + (_toRotate.y * cosf(_radians)));
}
