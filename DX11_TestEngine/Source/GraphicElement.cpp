#include "GraphicElement.h"
#include <math.h>

using namespace Vector3;
using namespace Vector4;

GraphicElement::GraphicElement(GraphicElementType _graphicElementType) : m_graphicElementType(_graphicElementType)
{

}

GraphicElement::GraphicElement(Vec3D _pos, GraphicElementType _graphicElementType) : m_graphicElementType(_graphicElementType)
{
	Translate(_pos);
}

GraphicElement::GraphicElement(std::vector<VertexColor>& _geometry, Vector3::Vec3D _pos, GraphicElementType _graphicElementType) : m_geometry(_geometry), m_graphicElementType(_graphicElementType)
{
	Translate(_pos);
}

GraphicElement::GraphicElement(std::vector<Vertex>& _geometry, Vector3::Vec3D _pos, GraphicElementType _graphicElementType) : m_graphicElementType(_graphicElementType)
{
	m_geometry.insert(m_geometry.begin(), _geometry.begin(), _geometry.end());

	Scale(Vec3D(1.0f, 1.0f, 0.0f));
	Translate(_pos);
}

Vec3D GraphicElement::GetPosition()
{
	return Vec3D(
		m_transform.GetElement(3, 0),
		m_transform.GetElement(3, 1),
		m_transform.GetElement(3, 2)
	);
}
Vec3D GraphicElement::GetScreenPosition()
{
	return Vec3D(
		m_transform.GetElement(3, 0) * WIDTH,
		m_transform.GetElement(3, 1) * HEIGHT,
		m_transform.GetElement(3, 2)
	);
}
Vec3D GraphicElement::GetScale()
{
	return Vec3D(
		m_transform.GetElement(0, 0),
		m_transform.GetElement(1, 1),
		m_transform.GetElement(2, 2)
	);
}
void GraphicElement::CalculateNormals()
{
	Vec3D vecA, vecB;
	for (int i = 0; i < m_geometry.size(); i += 3)
	{
		vecA = (m_geometry[i].pos - m_geometry[i + 1].pos);
		vecB = (m_geometry[i + 2].pos - m_geometry[i + 1].pos);
		m_geometry[i].normal = Vec3D((vecA.y * vecB.z) - (vecA.z * vecB.y),
									 (vecA.z * vecB.x) - (vecA.x * vecB.z), 
									 (vecA.x * vecB.y) - (vecA.y * vecB.x)).normalized() * -1.0f;
		m_geometry[i + 1].normal = m_geometry[i].normal;
		m_geometry[i + 2].normal = m_geometry[i].normal;
	}
}
void GraphicElement::Translate(Vector3::Vec3D _translate)
{
	Matrices::Matrix4x4 translateMatrix;

	translateMatrix.SetElement(3, 0, _translate.x);
	translateMatrix.SetElement(3, 1, _translate.y);
	translateMatrix.SetElement(3, 2, _translate.z);

	m_transform = m_transform * translateMatrix;
}
void GraphicElement::SetPosition(Vec3D _newPosition)
{
	m_transform.SetElement(3, 0, _newPosition.x);
	m_transform.SetElement(3, 1, _newPosition.y);
	m_transform.SetElement(3, 2, _newPosition.z);
}
void GraphicElement::SetScreenPosition(Vec3D _newPosition)
{
	//Vec3D viewPortPos;
	//viewPortPos.x = _newPosition.x / WIDTH;
	//viewPortPos.y = _newPosition.y / HEIGHT;
	//viewPortPos.z = _newPosition.z;
	//SetPosition(viewPortPos);


	m_transform.SetElement(0, 3, _newPosition.x / WIDTH);
	m_transform.SetElement(1, 3, _newPosition.y / HEIGHT);
	m_transform.SetElement(2, 3, _newPosition.z);
}

void GraphicElement::SetScale(Vec3D _newScale)
{
	m_transform.SetElement(0, 0, _newScale.x);
	m_transform.SetElement(1, 1, _newScale.y);
	m_transform.SetElement(2, 2, _newScale.z);
}

void GraphicElement::RotateGeometryOnZ(float _radians)
{
	Matrices::Matrix4x4 roationMatrix;

	roationMatrix.SetElement(0, 0, cosf(_radians));
	roationMatrix.SetElement(1, 0, -sinf(_radians));
	roationMatrix.SetElement(0, 1, sinf(_radians));
	roationMatrix.SetElement(1, 1, cosf(_radians));

	m_transform = m_transform * roationMatrix;

	//Update normals
	/*
	for (int i = 0; i < m_geometry.size(); i += 3)
	{
		m_geometry[i].normal.x = (m_geometry[i].normal.x * cosf(_radians)) - (m_geometry[i].normal.y * sinf(_radians));
		m_geometry[i].normal.y = (m_geometry[i].normal.x * sinf(_radians)) + (m_geometry[i].normal.y * cosf(_radians));
		m_geometry[i] = m_geometry[i].normal.normalized();
		m_geometry[i + 1] = m_geometry[i].normal;
		m_geometry[i + 2] = m_geometry[i].normal;
	}
	*/
}

void GraphicElement::RotateGeometryOnX(float _radians)
{
	Matrices::Matrix4x4 roationMatrix;

	roationMatrix.SetElement(1, 1, cosf(_radians));
	roationMatrix.SetElement(2, 1, -sinf(_radians));
	roationMatrix.SetElement(1, 2, sinf(_radians));
	roationMatrix.SetElement(2, 2, cosf(_radians));

	m_transform = m_transform * roationMatrix;

	//Update normals
	/*
	for (int i = 0; i < m_geometry.size(); i += 3)
	{
		m_geometry[i].normal.y = (m_geometry[i].normal.y * cosf(_radians)) - (m_geometry[i].normal.z * sinf(_radians));
		m_geometry[i].normal.z = (m_geometry[i].normal.y * sinf(_radians)) + (m_geometry[i].normal.z * cosf(_radians));
		m_geometry[i] = m_geometry[i].normal.normalized();
		m_geometry[i + 1] = m_geometry[i].normal;
		m_geometry[i + 2] = m_geometry[i].normal;
	}
	*/
}

void GraphicElement::RotateGeometryOnY(float _radians)
{
	Matrices::Matrix4x4 roationMatrix;

	roationMatrix.SetElement(0, 0, cosf(_radians));
	roationMatrix.SetElement(0, 2, -sinf(_radians));
	roationMatrix.SetElement(2, 0, sinf(_radians));
	roationMatrix.SetElement(2, 2, cosf(_radians));

	m_transform = m_transform * roationMatrix;

	//Update normals
	/*
	for (int i = 0; i < m_geometry.size(); i += 3)
	{
		m_geometry[i].normal.x = (m_geometry[i].normal.x * cosf(_radians)) + (m_geometry[i].normal.z * sinf(_radians));
		m_geometry[i].normal.z = (-m_geometry[i].normal.x * sinf(_radians)) + (m_geometry[i].normal.z * cosf(_radians));
		m_geometry[i] = m_geometry[i].normal.normalized();
		m_geometry[i + 1] = m_geometry[i].normal;
		m_geometry[i + 2] = m_geometry[i].normal;
	}
	*/
}

void GraphicElement::Scale(Vector3::Vec3D _newScale)
{
	Matrices::Matrix4x4 scaleMatrix;

	scaleMatrix.SetElement(0, 0, _newScale.x);
	scaleMatrix.SetElement(1, 1, _newScale.y);
	scaleMatrix.SetElement(2, 2, _newScale.z);

	m_transform = m_transform * scaleMatrix;
}
void GraphicElement::SetColor(Color _color)
{
	for (int i = 0; i < m_geometry.size(); i++)
	{
		m_geometry[i].color = _color;
	}
}

void GraphicElement::AppendGeometry(std::vector<VertexColor>& _newGeometry)
{
	m_geometry.insert(m_geometry.begin(), _newGeometry.begin(), _newGeometry.end());
}

GraphicElementType GraphicElement::GetGraphicElementType()
{
	return m_graphicElementType;
}

void GraphicElement::AddRenderFlag(GraphicElementRenderFlags _renderFlag)
{
	m_renderFlags |= (unsigned int)_renderFlag;
}

void GraphicElement::RemoveRenderFlag(GraphicElementRenderFlags _renderFlag)
{
	if((m_renderFlags & (unsigned int)_renderFlag) != 0)
		m_renderFlags -= (unsigned int)_renderFlag;
}

unsigned int GraphicElement::GetRenderFlags()
{
	return m_renderFlags;
}

Matrices::Matrix4x4& GraphicElement::GetTransform()
{
	return m_transform;
}

std::vector<VertexColor>& GraphicElement::GetGeometry()
{
	return m_geometry;
}
