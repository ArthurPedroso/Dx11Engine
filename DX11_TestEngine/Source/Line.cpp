#include "Line.h"

using namespace Vector3;
using namespace BasicElements;

std::array<Vector2::Vec2D, 2> BasicElements::Line::GetLineVertices()
{
    return m_lineVertices;
}

BasicElements::Line::Line(std::vector<Vertex>& _geometry, std::array<Vector2::Vec2D, 2>& _lineVertices, Vector3::Vec3D _pos, float _thickness) : GraphicElement(_geometry, _pos, GraphicElementType::Line), m_lineVertices(_lineVertices), m_thickness(_thickness)
{
}
