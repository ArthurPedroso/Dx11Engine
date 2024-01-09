#pragma once

#include "Common.h"
#include "Vectors.h"
#include "Matrices.h"
#include <vector>

enum class GraphicElementType : int
{
	Generic = 0,
	Point = 1,
	Line = 2,
	Circle = 3, 
	HollowTriangle = 4,
	HollowRectangle = 5,
	HollowPoly = 6
};

enum class GraphicElementRenderFlags : unsigned int
{
	Highlighted = 1U
};

class GraphicElement
{
protected:
	std::vector<VertexColor> m_geometry;
	Matrices::Matrix4x4 m_transform;
	GraphicElementType m_graphicElementType;
	unsigned int m_renderFlags;
public:
	//ConstantBuffer ConstantBuffer;
	GraphicElement(GraphicElementType _graphicElementType);
	GraphicElement(Vector3::Vec3D _pos, GraphicElementType _graphicElementType);
	GraphicElement(std::vector<VertexColor>& _geometry, Vector3::Vec3D _pos, GraphicElementType _graphicElementType);
	GraphicElement(std::vector<Vertex>& _geometry, Vector3::Vec3D _pos, GraphicElementType _graphicElementType);

	Vector3::Vec3D GetPosition();
	Vector3::Vec3D GetScreenPosition();
	Vector3::Vec3D GetScale();
	void CalculateNormals();
	void Translate(Vector3::Vec3D _translate);
	void SetPosition(Vector3::Vec3D _newPosition);
	void SetScreenPosition(Vector3::Vec3D _newPosition);
	void SetScale(Vector3::Vec3D _newScale);
	void RotateGeometryOnZ(float _radians);
	void RotateGeometryOnX(float _radians);
	void RotateGeometryOnY(float _radians);
	void Scale(Vector3::Vec3D _newScale);
	void SetColor(Color _color);
	void AppendGeometry(std::vector<VertexColor>& _newGeometry);
	GraphicElementType GetGraphicElementType();
	void AddRenderFlag(GraphicElementRenderFlags _renderFlag);
	void RemoveRenderFlag(GraphicElementRenderFlags _renderFlag);
	unsigned int GetRenderFlags();

	std::vector<VertexColor>& GetGeometry();
	Matrices::Matrix4x4& GetTransform();
};

