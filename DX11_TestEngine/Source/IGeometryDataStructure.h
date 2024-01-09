#pragma once

#include "GraphicElement.h"
#include <memory>

class IGeometryDataStructure
{
public:
	virtual std::shared_ptr<GraphicElement> get_item(int _itemIndex) = 0;
	virtual Matrices::Matrix4x4* GetProjectionMatrix() = 0;
	virtual Matrices::Matrix4x4* GetViewMatrix() = 0;
	virtual Vector3::Vec3D* GetGlobalLight() = 0;
	virtual void push_back(std::shared_ptr<GraphicElement> _newInsertItem) = 0;
	virtual void pop_back() = 0;
	virtual void clear() = 0;
	virtual int size() = 0;
};

