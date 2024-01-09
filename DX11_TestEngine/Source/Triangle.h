#pragma once

#include "GraphicElement.h"

namespace BasicElements
{
	class Triangle : public GraphicElement
	{
	public:
		Triangle(Color _color, GraphicElementType _graphicElementType);
		Triangle(Color _color, Vector3::Vec3D _pos, GraphicElementType _graphicElementType);
		Triangle(Color _color, float _startingSize, GraphicElementType _graphicElementType);
		Triangle(Color _color, Vector3::Vec3D _pos, float _startingSize, GraphicElementType _graphicElementType);
	};
}

