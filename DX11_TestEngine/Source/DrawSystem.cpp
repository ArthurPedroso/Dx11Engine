#include "DrawSystem.h"
#include "Quad.h"
#include "Circle.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <chrono>

using namespace Vector2;
using namespace Vector3;
using namespace Vector4;
using namespace BasicElements;


DrawSystem::DrawSystem(float _pixelSize) : m_pixelSize(_pixelSize)
{
}
