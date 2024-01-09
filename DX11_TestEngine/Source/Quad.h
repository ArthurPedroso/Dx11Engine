#pragma once

#include "GraphicElement.h"
#include "IGeometryDataStructure.h"

namespace BasicElements
{
	class Quad : public GraphicElement
	{
	public:
		Quad(Color _color, GraphicElementType _graphicElementType);
		Quad(Color _color, Vector3::Vec3D _pos, GraphicElementType _graphicElementType);
		Quad(Color _color, float _startingSize, GraphicElementType _graphicElementType);
		Quad(Color _color, Vector3::Vec3D _pos, float _startingSize, GraphicElementType _graphicElementType);
	};
	typedef Quad Pixel;
}

