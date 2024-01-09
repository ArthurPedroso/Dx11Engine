#include "HollowRect.h"

using namespace std;
using namespace BasicElements;

std::array<Vector2::Vec2D, 2> BasicElements::HollowRect::GetRectVertices()
{
	return m_rectVertices;
}

BasicElements::HollowRect::HollowRect(std::vector<Vertex>& _geometry, std::array<Vector2::Vec2D, 2>& _rectVertices, Vector3::Vec3D _pos, float _thickness) : GraphicElement(_geometry, _pos, GraphicElementType::HollowRectangle), m_rectVertices(_rectVertices), m_thickness(_thickness)
{
}
