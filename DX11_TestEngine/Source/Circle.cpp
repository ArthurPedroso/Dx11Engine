#include "Circle.h"
#include "SimpleGeometry.h"
#include <array>

using namespace Vector3;
using namespace BasicElements;

Circle::Circle(Color _color, Vec3D _pos, float _startingSize, GraphicElementType _graphicElementType, int _thickness) : GraphicElement(_graphicElementType), m_thickness(_thickness)
{
	m_geometry.insert(m_geometry.begin(), std::begin(PrimitiveGeometry::k_circleGeometry), std::end(PrimitiveGeometry::k_circleGeometry));

	Scale(Vec3D((float)HEIGHT / (float)WIDTH, 1.0f, 0.0f));
	Scale(Vec3D(Vector2::Vec2One, 0.0f) * _startingSize);
	Translate(_pos);
	SetColor(_color);
}
