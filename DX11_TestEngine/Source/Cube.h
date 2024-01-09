#pragma once

#include "GraphicElement.h"
#include "IGeometryDataStructure.h"

namespace BasicElements
{
	class Cube : public GraphicElement
	{
	public:
		Cube(Color _color, Vector3::Vec3D _pos, float _startingSize, GraphicElementType _graphicElementType);
	};
}

