#include "Cube.h"
#include "SimpleGeometry.h"
#include "Vectors.h"

using namespace Vector3;

BasicElements::Cube::Cube(Color _color, Vector3::Vec3D _pos, float _startingSize, GraphicElementType _graphicElementType) : GraphicElement(_graphicElementType)
{
	m_geometry.insert(m_geometry.begin(), std::begin(PrimitiveGeometry::k_cubeGeometry), std::end(PrimitiveGeometry::k_cubeGeometry));
	CalculateNormals();
	//Scale(Vec3D((float)HEIGHT / (float)WIDTH, 1.0f, 1.0f));
	Scale(Vec3One * _startingSize);
	SetPosition(_pos);
	SetColor(_color);
}
