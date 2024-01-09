#pragma once

#include "GraphicElement.h"
#include "Vectors.h"
#include <vector>

namespace BasicElements
{
	class HollowPoly : public GraphicElement
	{
	private:
		float m_thickness;
		std::vector<Vector2::Vec2D> m_polyLines;
	public:
		std::vector<Vector2::Vec2D> GetPolyLines();
		float GetThickness() { return m_thickness; }

		HollowPoly(std::vector<Vertex>& _geometry, std::vector<Vector2::Vec2D>& _polyLines, Vector3::Vec3D _pos, float _thickness);

	};
}

