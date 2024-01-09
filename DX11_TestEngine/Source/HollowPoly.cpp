#include "HollowPoly.h"

using namespace std;
using namespace BasicElements;

vector<Vector2::Vec2D> HollowPoly::GetPolyLines()
{
    return m_polyLines;
}

HollowPoly::HollowPoly(vector<Vertex>& _geometry, vector<Vector2::Vec2D>& _polyLines, Vector3::Vec3D _pos, float _thickness) : GraphicElement(_geometry, _pos, GraphicElementType::HollowPoly), m_polyLines(_polyLines), m_thickness(_thickness)
{
}
