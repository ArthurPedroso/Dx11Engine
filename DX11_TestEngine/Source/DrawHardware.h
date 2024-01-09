#pragma once

#include "DrawSystem.h"
#include <vector>

class DrawHardware : public DrawSystem
{
protected:
	std::vector<Vertex> CreateLineGeometry(Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, float _thickness);
public:
	virtual void DrawRect(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, Color _color, float _thickness)override;
	virtual void DrawCircle(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _centerVertex, float _radius, Color _color, int _thickness = 0)override;
	virtual void DrawLine(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, Color _color, float _thickness)override;
	virtual void DrawPixel(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _position, Color _color, float _size)override;
	virtual void DrawTriangle(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, Vector3::Vec3D _vertexC, Color _color, float _size)override;
	virtual void DrawPoly(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _position, Color _color, std::vector<Vector2::Vec2D>& _vertices, float _size)override;


	using DrawSystem::DrawSystem;
};

