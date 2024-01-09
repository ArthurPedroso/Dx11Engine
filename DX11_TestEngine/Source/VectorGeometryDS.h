#pragma once

#include "IGeometryDataStructure.h"

class VectorGeometryDS : public IGeometryDataStructure
{
private:
	
//fields:
	std::vector<VertexColor> m_appGeometry;
	std::vector<int> m_graphicElementSize;
	std::vector<Matrices::Matrix4x4> m_geometryTransforms;

//Methods:
	int GetGeometryBeginPos(int _elementIndex);
public:
	VectorGeometryDS();

	virtual VertexColor* operator[](int _index) override;

	virtual int AddNewElement(VertexColor _newGeometry[], int _arrayLength) override;
	virtual int AddNewElement(const Vertex _newGeometry[], int _arrayLength, Vector4::Vec4D _color) override;
	virtual int AddNewElement(std::vector<VertexColor>& _newGeometry) override;
	virtual int AddNewElement(std::vector<Vertex>& _newGeometry, Vector4::Vec4D _color) override;
	virtual Matrices::Matrix4x4& GetElementTransform(int _elementIndex) override;
	virtual void RemoveElement(int _elementIndex) override;
	virtual int Size() override;
};

