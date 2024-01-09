#pragma once

#include "GraphicElement.h"
#include "IGeometryDataStructure.h"

namespace BasicElements
{
	class Circle : public GraphicElement
	{
	private:
		int m_thickness;
	public:
		int GetThickness() { return m_thickness; }

		Circle(Color _color, Vector3::Vec3D _pos, float _startingSize, GraphicElementType _graphicElementType, int _thickness);
	};
}

