#include "Quad.h"
#include "SimpleGeometry.h"
#include <array>

using namespace Vector3;
using namespace BasicElements;

Quad::Quad(Color _color, GraphicElementType _graphicElementType) : GraphicElement(_graphicElementType)
{
	m_geometry.insert(m_geometry.begin(), std::begin(PrimitiveGeometry::k_quadGeometry), std::end(PrimitiveGeometry::k_quadGeometry));

	Scale(Vec3D((float)HEIGHT / (float)WIDTH, 1.0f, 0.0f));
	SetColor(_color);
}

Quad::Quad(Color _color, Vector3::Vec3D _pos, GraphicElementType _graphicElementType) : GraphicElement(_graphicElementType)
{
	m_geometry.insert(m_geometry.begin(), std::begin(PrimitiveGeometry::k_quadGeometry), std::end(PrimitiveGeometry::k_quadGeometry));

	Scale(Vec3D((float)HEIGHT / (float)WIDTH, 1.0f, 0.0f));
	SetPosition(_pos);
	SetColor(_color);
}

Quad::Quad(Color _color, float _startingSize, GraphicElementType _graphicElementType) : GraphicElement(_graphicElementType)
{
	m_geometry.insert(m_geometry.begin(), std::begin(PrimitiveGeometry::k_quadGeometry), std::end(PrimitiveGeometry::k_quadGeometry));

	Scale(Vec3D((float)HEIGHT / (float)WIDTH, 1.0f, 0.0f));
	Scale(Vec3One * _startingSize);
	SetColor(_color);
}

Quad::Quad(Color _color, Vec3D _pos, float _startingSize, GraphicElementType _graphicElementType) : GraphicElement(_graphicElementType)
{
	m_geometry.insert(m_geometry.begin(), std::begin(PrimitiveGeometry::k_quadGeometry), std::end(PrimitiveGeometry::k_quadGeometry));

	Scale(Vec3D((float)HEIGHT / (float)WIDTH, 1.0f, 0.0f));
	Scale(Vec3One * _startingSize);
	SetPosition(_pos);
	SetColor(_color);
}

