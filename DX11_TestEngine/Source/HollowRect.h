#pragma once

#include "GraphicElement.h"
#include "Vectors.h"
#include <array>


namespace BasicElements
{
	class HollowRect : public GraphicElement
	{
	private:
		float m_thickness;
		std::array<Vector2::Vec2D, 2> m_rectVertices;
	public:
		std::array<Vector2::Vec2D, 2> GetRectVertices();
		float GetThickness() { return m_thickness; }

		HollowRect(std::vector<Vertex>& _geometry, std::array<Vector2::Vec2D, 2>& _rectVertices, Vector3::Vec3D _pos, float _thickness);

	};
}

