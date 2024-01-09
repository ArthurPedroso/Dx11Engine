#include "HollowTriangle.h"

using namespace std;
using namespace BasicElements;

array<Vector2::Vec2D, 3> HollowTriangle::GetTriangleVertices()
{
	return m_triangleVertices;
}

HollowTriangle::HollowTriangle(vector<Vertex>& _geometry, array<Vector2::Vec2D, 3>& _triangleVertices, Vector3::Vec3D _pos, float _thickness) : GraphicElement(_geometry, _pos, GraphicElementType::HollowTriangle), m_triangleVertices(_triangleVertices), m_thickness(_thickness)
{
}
