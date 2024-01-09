#include "VectorGeometryDS.h"

//-----PRIVATE-----//
int VectorGeometryDS::GetGeometryBeginPos(int _elementIndex)
{
    int geometryBeginPos = 0;

    for (int i = 0; i < _elementIndex; i++)
    {
        geometryBeginPos += m_graphicElementSize[i];
    }

    return geometryBeginPos;
}
//-----PRIVATE-----//


//-----PUBLIC------//
VectorGeometryDS::VectorGeometryDS()
{
}

VertexColor* VectorGeometryDS::operator[](int _index)
{
    return &m_appGeometry[GetGeometryBeginPos(_index)];
}

int VectorGeometryDS::AddNewElement(VertexColor _newGeometry[], int _arrayLength)
{
    if (_newGeometry == nullptr || _arrayLength == 0) throw std::bad_exception();

    for (int i = 0; i < _arrayLength; i++)
    {
        m_appGeometry.push_back(_newGeometry[i]);
    }
    m_graphicElementSize.push_back(_arrayLength);
    m_geometryTransforms.push_back(Matrices::Matrix4x4());

    return m_graphicElementSize.size() - 1;
}

int VectorGeometryDS::AddNewElement(const Vertex _newGeometry[], int _arrayLength, Vector4::Vec4D _color)
{
    if (_newGeometry == nullptr || _arrayLength == 0) throw std::bad_exception();

    for (int i = 0; i < _arrayLength; i++)
    {
        m_appGeometry.push_back(VertexColor(_newGeometry[i], _color));
    }
    m_graphicElementSize.push_back(_arrayLength);
    m_geometryTransforms.push_back(Matrices::Matrix4x4());

    return m_graphicElementSize.size() - 1;
}

int VectorGeometryDS::AddNewElement(std::vector<VertexColor>& _newGeometry)
{
    if (_newGeometry.size() == 0) throw std::bad_exception();

    m_appGeometry.insert(m_appGeometry.begin(), _newGeometry.begin(), _newGeometry.end());
    m_graphicElementSize.push_back(_newGeometry.size());
    m_geometryTransforms.push_back(Matrices::Matrix4x4());

    return m_graphicElementSize.size() - 1;
}

int VectorGeometryDS::AddNewElement(std::vector<Vertex>& _newGeometry, Vector4::Vec4D _color)
{
    if (_newGeometry.size() == 0) throw std::bad_exception();

    for (int i = 0; i < _newGeometry.size(); i++)
    {
        m_appGeometry.push_back(VertexColor(_newGeometry[i], _color));
    }
    m_graphicElementSize.push_back(_newGeometry.size());
    m_geometryTransforms.push_back(Matrices::Matrix4x4());

    return m_graphicElementSize.size() - 1;
}

Matrices::Matrix4x4& VectorGeometryDS::GetElementTransform(int _elementIndex)
{
    if(_elementIndex >= m_geometryTransforms.size()) throw std::bad_exception();

    return m_geometryTransforms[_elementIndex];
}

void VectorGeometryDS::RemoveElement(int _elementIndex)
{
    int geometrySize = m_graphicElementSize[_elementIndex];
    int geometryBeginIndex = GetGeometryBeginPos(_elementIndex);

    m_appGeometry.erase(m_appGeometry.begin() + geometryBeginIndex, m_appGeometry.begin() + geometryBeginIndex + geometrySize - 1);
    m_graphicElementSize.erase(m_graphicElementSize.begin() + _elementIndex);
    m_geometryTransforms.erase(m_geometryTransforms.begin() + _elementIndex);
}
int VectorGeometryDS::Size()
{
    return m_appGeometry.size();
}
//-----PUBLIC------//
