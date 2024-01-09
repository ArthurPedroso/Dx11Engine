#pragma once

#include "GraphicElement.h"
#include "Vectors.h"
#include <array>

namespace BasicElements
{
	class Line : public GraphicElement
	{
	private:
		float m_thickness;
		std::array<Vector2::Vec2D, 2> m_lineVertices;
	public:
		std::array<Vector2::Vec2D, 2> GetLineVertices();
		float GetThickness() { return m_thickness; }

		Line(std::vector<Vertex>& _geometry, std::array<Vector2::Vec2D, 2>& _lineVertices, Vector3::Vec3D _pos, float _thickness);
	};
}
