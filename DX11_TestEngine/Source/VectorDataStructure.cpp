#include "VectorDataStructure.h"

using namespace Vector3;

VectorDataStructure::VectorDataStructure() : m_getGlobalLight(Vec3D(1.0f, 1.0f, -1.0f).normalized())
{
    m_projectionMatrix.SetElement(2, 2, 0.1f);
    //m_projectionMatrix.SetElement(1, 1, ((float)WIDTH / (float)HEIGHT));

    m_viewMatrix.SetElement(3, 2, 5);
}

Matrices::Matrix4x4* VectorDataStructure::GetProjectionMatrix()
{
    return &m_projectionMatrix;
}

Matrices::Matrix4x4* VectorDataStructure::GetViewMatrix()
{
    return &m_viewMatrix;
}

Vector3::Vec3D* VectorDataStructure::GetGlobalLight()
{
    return &m_getGlobalLight;
}

std::shared_ptr<GraphicElement> VectorDataStructure::get_item(int _itemIndex)
{
    return m_geometryData[_itemIndex];
}

void VectorDataStructure::push_back(std::shared_ptr<GraphicElement> _newInsertItem)
{
    m_geometryData.push_back(_newInsertItem);
}

void VectorDataStructure::pop_back()
{
    m_geometryData.pop_back();
}

void VectorDataStructure::clear()
{
    m_geometryData.clear();
}

int VectorDataStructure::size()
{
    return m_geometryData.size();
}
