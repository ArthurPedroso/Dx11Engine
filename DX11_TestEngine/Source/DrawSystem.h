#pragma once

#include "GraphicElement.h"
#include "MathLib.h"
#include "IGeometryDataStructure.h"
#include <vector>
#include <memory>
#include <array>


class DrawSystem
{
protected:
	float m_pixelSize;
public:
	DrawSystem(float _pixelSize);
	//Virtual:
	virtual void DrawRect(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, Color _color, float _thickness) = 0;
	virtual void DrawCircle(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _centerVertex, float _radius, Color _color, int _thickness = 0) = 0;
	virtual void DrawLine(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, Color _color, float _thickness) = 0;
	virtual void DrawPixel(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _position, Color _color, float _size) = 0;
	virtual void DrawTriangle(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, Vector3::Vec3D _vertexC, Color _color, float _size) = 0;
	virtual void DrawPoly(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _position, Color _color, std::vector<Vector2::Vec2D>& _vertices, float _size) = 0;
};

