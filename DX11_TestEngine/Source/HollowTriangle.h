#pragma once

#include "GraphicElement.h"
#include "Vectors.h"
#include <array>


namespace BasicElements
{
	class HollowTriangle : public GraphicElement
	{
	private:
		float m_thickness;
		std::array<Vector2::Vec2D, 3> m_triangleVertices;
	public:
		std::array<Vector2::Vec2D, 3> GetTriangleVertices();
		float GetThickness() { return m_thickness; }

		HollowTriangle(std::vector<Vertex>& _geometry, std::array<Vector2::Vec2D, 3>& _triangleVertices, Vector3::Vec3D _pos, float _thickness);

	};
}

