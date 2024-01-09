#include "Vectors.h"


#define _USE_MATH_DEFINES
#include <math.h>

float Vector2::Vec2D::magnitude()
{
    return sqrtf((x*x) + (y*y));
}

float Vector2::VecInt2D::magnitude()
{
    return sqrtf((x * x) + (y * y));
}

float Vector2::VecInt2D::vectorAngle()
{
    Vector2::Vec2D normalized = this->normalized();
    float arcSin;

    arcSin = asinf(normalized.y);

    if (normalized.x < 0)
    {
        if (arcSin >= 0.0f)
            arcSin = M_PI - arcSin;
        else
            arcSin = (-M_PI) - arcSin;
    }


    return arcSin;
}
float Vector2::Vec2D::vectorAngle()
{
    Vector2::Vec2D normalized = this->normalized();
    float arcSin;

    arcSin = asinf(normalized.y);

    if (normalized.x < 0)
    {
        if (arcSin >= 0.0f)
            arcSin = M_PI - arcSin;
        else
            arcSin = (-M_PI) - arcSin;
    }


    return arcSin;
}

void Vector2::Vec2D::rotate(float _a)
{
    float oldX = x;
    x = x * cosf(_a) - y * sinf(_a);
    y = oldX * sinf(_a) + y * cosf(_a);
}

Vector2::Vec2D Vector2::Vec2D::normalized()
{
    float magnitude = sqrtf((x * x) + (y * y));
    return Vec2D(x / magnitude, y / magnitude);
}


Vector2::Vec2D Vector2::VecInt2D::normalized()
{
    float magnitude = sqrtf((x * x) + (y * y));
    return Vec2D(x / magnitude, y / magnitude);
}

float Vector3::Vec3D::magnitude()
{
    float xyMagnitude = sqrtf((x * x) + (y * y));
    return sqrtf((xyMagnitude * xyMagnitude) + (z * z));
}

Vector3::Vec3D Vector3::Vec3D::normalized()
{
    return (*this) / ((*this).magnitude());
}
