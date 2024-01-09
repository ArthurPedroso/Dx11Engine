#pragma once

#include "IGeometryDataStructure.h"
#include <vector>

class VectorDataStructure : public IGeometryDataStructure
{
private:
	std::vector<std::shared_ptr<GraphicElement>> m_geometryData;
	Matrices::Matrix4x4 m_projectionMatrix;
	Matrices::Matrix4x4 m_viewMatrix;
	Vector3::Vec3D m_getGlobalLight;
public:
	VectorDataStructure();

	virtual Matrices::Matrix4x4* GetProjectionMatrix() override;
	virtual Matrices::Matrix4x4* GetViewMatrix() override;
	virtual Vector3::Vec3D* GetGlobalLight() override;
	virtual std::shared_ptr<GraphicElement> get_item(int _itemIndex) override;
	virtual void push_back(std::shared_ptr<GraphicElement> _newInsertItem) override;
	virtual void pop_back() override;
	virtual void clear() override;
	virtual int size() override;
};

