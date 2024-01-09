#include "DrawHardware.h"
#include "SimpleGeometry.h"

#include "Quad.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"
#include "HollowTriangle.h"
#include "HollowRect.h"
#include "HollowPoly.h"
#include <array>
#include <math.h>

using namespace PrimitiveGeometry;
using namespace BasicElements;

std::vector<Vertex> DrawHardware::CreateLineGeometry(Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, float _thickness)
{
    std::vector<Vertex> newQuad;
    Vec2D vecA(_vertexA.x, _vertexA.y);
    Vec2D vecB(_vertexB.x, _vertexB.y);

    Vec2D newPos = vecA + ((vecB - vecA) / 2);
    float width = (vecB - vecA).magnitude() / 2;

    float angle = (vecB - vecA).vectorAngle();
    int i;
    Vec2D tempVec;

    newQuad.insert(newQuad.begin(), std::begin(PrimitiveGeometry::k_quadGeometry), std::end(PrimitiveGeometry::k_quadGeometry));

    for (i = 0; i < newQuad.size(); i++)
    {
        tempVec = Vec2D(newQuad[i].x, newQuad[i].y);
        tempVec.x *= width;
        tempVec.y *= _thickness;

        tempVec.rotate(angle);

        tempVec += newPos;

        newQuad[i].x = tempVec.x;
        newQuad[i].y = tempVec.y;
    }

    return newQuad;
}

void DrawHardware::DrawRect(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, Color _color, float _thickness)
{
    std::shared_ptr<GraphicElement> newElement;
    std::vector<Vertex> newRect;
    std::vector<Vertex> tempLine;
    std::array<Vector2::Vec2D, 2> vertices;

    Vec3D rectPos = _vertexA + ((_vertexB - _vertexA) / 2);
    Vec3D normalizedVertexA;
    Vec3D normalizedVertexB;

    normalizedVertexA = _vertexA - rectPos;
    normalizedVertexB = _vertexB - rectPos;
    vertices[0] = Vec2D(_vertexA.x, _vertexA.y);
    vertices[1] = Vec2D(_vertexB.x, _vertexB.y);

    newRect = CreateLineGeometry(normalizedVertexA, Vec3D(normalizedVertexB.x, normalizedVertexA.y, 0.0f), _thickness);

    tempLine = CreateLineGeometry(normalizedVertexB, Vec3D(normalizedVertexA.x, normalizedVertexB.y, 0.0f), _thickness);
    newRect.insert(newRect.begin(), tempLine.begin(), tempLine.end());

    tempLine = CreateLineGeometry(normalizedVertexB, Vec3D(normalizedVertexB.x, normalizedVertexA.y, 0.0f), _thickness);
    newRect.insert(newRect.begin(), tempLine.begin(), tempLine.end());

    tempLine = CreateLineGeometry(normalizedVertexA, Vec3D(normalizedVertexA.x, normalizedVertexB.y, 0.0f), _thickness);
    newRect.insert(newRect.begin(), tempLine.begin(), tempLine.end());

    newElement = std::make_shared<HollowRect>(newRect, vertices, rectPos, _thickness);
    newElement.get()->SetColor(_color);

    _geometryBuffer.get()->push_back(newElement);
}

void DrawHardware::DrawCircle(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _centerVertex, float _radius, Color _color, int _thickness)
{
    _geometryBuffer.get()->push_back(std::make_shared<Circle>(_color, _centerVertex, _radius, _graphicElementType, _thickness));
}

void DrawHardware::DrawLine(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, Color _color, float _thickness)
{
    std::shared_ptr<GraphicElement> newElement;
    std::vector<Vertex> newLine;
    std::array<Vector2::Vec2D, 2> vertices;
    
    Vec3D linePos = _vertexA + ((_vertexB - _vertexA) / 2);
    Vec3D normalizedVertexA;
    Vec3D normalizedVertexB;
    normalizedVertexA = _vertexA - linePos;
    normalizedVertexB = _vertexB - linePos;

    vertices[0] = Vec2D(_vertexA.x, _vertexA.y);
    vertices[1] = Vec2D(_vertexB.x, _vertexB.y);
    
    newLine = CreateLineGeometry(normalizedVertexA, normalizedVertexB, _thickness);
    newElement = std::make_shared<Line>(newLine, vertices, linePos, _thickness);
    newElement.get()->SetColor(_color);
    
    _geometryBuffer.get()->push_back(newElement);
}

void DrawHardware::DrawPixel(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _position, Color _color, float _thickness)
{
    _geometryBuffer.get()->push_back(std::make_shared<Pixel>(_color, _position, _thickness, _graphicElementType));
}

void DrawHardware::DrawTriangle(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _vertexA, Vector3::Vec3D _vertexB, Vector3::Vec3D _vertexC, Color _color, float _thickness)
{
    std::shared_ptr<GraphicElement> newElement;
    std::vector<Vertex> newTri;
    std::vector<Vertex> tempLine;
    std::array<Vector2::Vec2D, 3> vertices;

    Vec3D triPos = _vertexA;
    Vec3D normalizedVertexA;
    Vec3D normalizedVertexB;
    Vec3D normalizedVertexC;
    normalizedVertexA = _vertexA - triPos;
    normalizedVertexB = _vertexB - triPos;
    normalizedVertexC = _vertexC - triPos;

    vertices[0] = Vec2D(_vertexA.x, _vertexA.y);
    vertices[1] = Vec2D(_vertexB.x, _vertexB.y);
    vertices[2] = Vec2D(_vertexC.x, _vertexC.y);

    newTri = CreateLineGeometry(normalizedVertexA, normalizedVertexB, _thickness);

    tempLine = CreateLineGeometry(normalizedVertexB, normalizedVertexC, _thickness);
    newTri.insert(newTri.begin(), tempLine.begin(), tempLine.end());

    tempLine = CreateLineGeometry(normalizedVertexC, normalizedVertexA, _thickness);
    newTri.insert(newTri.begin(), tempLine.begin(), tempLine.end());

    newElement = std::make_shared<HollowTriangle>(newTri, vertices, triPos, _thickness);
    newElement.get()->SetColor(_color);

    _geometryBuffer.get()->push_back(newElement);
}

void DrawHardware::DrawPoly(GraphicElementType _graphicElementType, std::shared_ptr<IGeometryDataStructure> _geometryBuffer, Vector3::Vec3D _position, Color _color, std::vector<Vector2::Vec2D>& _vertices, float _size)
{

    std::shared_ptr<GraphicElement> newElement;
    std::vector<Vertex> newPoly;
    std::vector<Vertex> tempLine;
    int i = 1;

    Vec2D polyPos = _vertices[0];
    Vec3D normalizedVertexA;
    Vec3D normalizedVertexB;

    for (; i < _vertices.size(); i++)
    {
        normalizedVertexA = Vec3D(_vertices[i] - polyPos, 0.0f);
        normalizedVertexB = Vec3D(_vertices[i - 1] - polyPos, 0.0f);

        tempLine = CreateLineGeometry(normalizedVertexA, normalizedVertexB, _size);
        newPoly.insert(newPoly.begin(), tempLine.begin(), tempLine.end());
    }
    normalizedVertexA = Vec3D(_vertices[0] - polyPos, 0.0f);
    normalizedVertexB = Vec3D(_vertices[i - 1] - polyPos, 0.0f);

    tempLine = CreateLineGeometry(normalizedVertexA, normalizedVertexB, _size);
    newPoly.insert(newPoly.begin(), tempLine.begin(), tempLine.end());

    newElement = std::make_shared<HollowPoly>(newPoly, _vertices, Vec3D(polyPos, 0.0f), _size);
    newElement.get()->SetColor(_color);

    _geometryBuffer.get()->push_back(newElement);
}
