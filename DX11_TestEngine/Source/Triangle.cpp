#include "Triangle.h"
#include "SimpleGeometry.h"
#include <array>

using namespace Vector3;
using namespace BasicElements;

Triangle::Triangle(Color _color, GraphicElementType _graphicElementType) : GraphicElement(_graphicElementType)
{
	m_geometry.insert(m_geometry.begin(), std::begin(PrimitiveGeometry::k_triangleGeometry), std::end(PrimitiveGeometry::k_triangleGeometry));
	SetColor(_color);
	Scale(Vec3D((float)HEIGHT / (float)WIDTH, 1.0f, 0.0f));
}

Triangle::Triangle(Color _color, Vector3::Vec3D _pos, GraphicElementType _graphicElementType) : GraphicElement(_graphicElementType)
{
	m_geometry.insert(m_geometry.begin(), std::begin(PrimitiveGeometry::k_triangleGeometry), std::end(PrimitiveGeometry::k_triangleGeometry));

	Scale(Vec3D((float)HEIGHT / (float)WIDTH, 1.0f, 0.0f));
	SetPosition(_pos);
	SetColor(_color);
}

Triangle::Triangle(Color _color, float _startingSize, GraphicElementType _graphicElementType) : GraphicElement(_graphicElementType)
{
	m_geometry.insert(m_geometry.begin(), std::begin(PrimitiveGeometry::k_triangleGeometry), std::end(PrimitiveGeometry::k_triangleGeometry));

	Scale(Vec3D((float)HEIGHT / (float)WIDTH, 1.0f, 0.0f));
	Scale(Vec3D(Vector2::Vec2One, 0.0f) * _startingSize);
	SetColor(_color);
}

Triangle::Triangle(Color _color, Vec3D _pos, float _startingSize, GraphicElementType _graphicElementType) : GraphicElement(_graphicElementType)
{
	m_geometry.insert(m_geometry.begin(), std::begin(PrimitiveGeometry::k_triangleGeometry), std::end(PrimitiveGeometry::k_triangleGeometry));

	Scale(Vec3D((float)HEIGHT / (float)WIDTH, 1.0f, 0.0f));
	Scale(Vec3D(Vector2::Vec2One, 0.0f) * _startingSize);
	SetPosition(_pos);
	SetColor(_color);
}

