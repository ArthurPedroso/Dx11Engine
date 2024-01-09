#pragma once

#include "Vectors.h"
#include <math.h>

using namespace Vector2;
using namespace Vector3;
using namespace Vector4;
/// <summary>
/// Classe estatica. Contem uma biblioteca de funcs matematicas
/// </summary>
class MathLib
{
public:
	static float VecDistance(Vec2D _vecA, Vec2D _vecB);
	static Vec2D VecRotate(Vec2D _roRotate, float _radians);
};

