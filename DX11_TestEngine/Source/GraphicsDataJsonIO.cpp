#include "GraphicsDataJsonIO.h"
#include "Quad.h"
#include "Circle.h"
#include "Triangle.h"
#include "Vectors.h"
#include "Line.h"
#include "HollowTriangle.h"
#include "HollowRect.h"
#include "HollowPoly.h"

#include <array>
#include <fstream>
#include <math.h>

using namespace std;
using namespace BasicElements;
using namespace Vector2;
using namespace Vector3;
using namespace Vector4;

void GraphicsDataJsonIO::ParsePixels(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem)
{
	Vec3D position;
	Color color;
	float size;
	for (int i = 0; i < _jsonValue.size(); i++)
	{
		position = Vec3D(_jsonValue[i]["coord"][0].asFloat(), _jsonValue[i]["coord"][1].asFloat(), 0.0f);
		color = Color(
			(unsigned char)_jsonValue[i]["cor"][0].asInt(),
			(unsigned char)_jsonValue[i]["cor"][1].asInt(),
			(unsigned char)_jsonValue[i]["cor"][2].asInt(),
			255);
		size = _jsonValue[i]["esp"].asFloat() * m_pixelSize;
		position = (position + Vec3D(-0.5f, -0.5f, 0.0f)) * 2.0f;
		position.y *= -1;
		_drawSystem.DrawPixel(GraphicElementType::Point, _graphicsVector, position, color, size);
	}
}

void GraphicsDataJsonIO::ParseLines(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem)
{
	Vec3D positionA, positionB;
	Color color;
	float size;
	for (int i = 0; i < _jsonValue.size(); i++)
	{
		positionA = Vec3D(_jsonValue[i]["pontos"][0][0].asFloat(), _jsonValue[i]["pontos"][0][1].asFloat(), 0.0f);
		positionB = Vec3D(_jsonValue[i]["pontos"][1][0].asFloat(), _jsonValue[i]["pontos"][1][1].asFloat(), 0.0f);
		color = Color(
			(unsigned char)_jsonValue[i]["cor"][0].asInt(),
			(unsigned char)_jsonValue[i]["cor"][1].asInt(),
			(unsigned char)_jsonValue[i]["cor"][2].asInt(),
			255);
		size = _jsonValue[i]["esp"].asFloat() * m_pixelSize;
		positionA = (positionA + Vec3D(-0.5f, -0.5f, 0.0f)) * 2.0f;
		positionA.y *= -1;
		positionB = (positionB + Vec3D(-0.5f, -0.5f, 0.0f)) * 2.0f;
		positionB.y *= -1;
		_drawSystem.DrawLine(GraphicElementType::Line, _graphicsVector, positionA, positionB, color, size);
	}
}

void GraphicsDataJsonIO::ParseCircles(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem)
{
	Vec3D position;
	Color color;
	float size;
	for (int i = 0; i < _jsonValue.size(); i++)
	{
		position = Vec3D(_jsonValue[i]["centro"][0].asFloat(), _jsonValue[i]["centro"][1].asFloat(), 0.0f);
		color = Color(
			(unsigned char)_jsonValue[i]["cor"][0].asInt(),
			(unsigned char)_jsonValue[i]["cor"][1].asInt(),
			(unsigned char)_jsonValue[i]["cor"][2].asInt(),
			255);
		size = _jsonValue[i]["raio"].asFloat();
		position = (position + Vec3D(-0.5f, -0.5f, 0.0f)) * 2.0f;
		position.y *= -1;
		_drawSystem.DrawCircle(GraphicElementType::Circle, _graphicsVector, position, size, color, _jsonValue[i]["esp"].asInt());
	}
}

void GraphicsDataJsonIO::ParseTriangles(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem)
{
	Vec3D positionA, positionB, positionC;
	Color color;
	float size;
	for (int i = 0; i < _jsonValue.size(); i++)
	{
		positionA = Vec3D(_jsonValue[i]["pontos"][0][0].asFloat(), _jsonValue[i]["pontos"][0][1].asFloat(), 0.0f);
		positionB = Vec3D(_jsonValue[i]["pontos"][1][0].asFloat(), _jsonValue[i]["pontos"][1][1].asFloat(), 0.0f);
		positionC = Vec3D(_jsonValue[i]["pontos"][2][0].asFloat(), _jsonValue[i]["pontos"][2][1].asFloat(), 0.0f);
		color = Color(
			(unsigned char)_jsonValue[i]["cor"][0].asInt(),
			(unsigned char)_jsonValue[i]["cor"][1].asInt(),
			(unsigned char)_jsonValue[i]["cor"][2].asInt(),
			255);
		size = _jsonValue[i]["esp"].asFloat() * m_pixelSize;

		positionA = (positionA + Vec3D(-0.5f, -0.5f, 0.0f)) * 2.0f;
		positionA.y *= -1;
		positionB = (positionB + Vec3D(-0.5f, -0.5f, 0.0f)) * 2.0f;
		positionB.y *= -1;
		positionC = (positionC + Vec3D(-0.5f, -0.5f, 0.0f)) * 2.0f;
		positionC.y *= -1;
		_drawSystem.DrawTriangle(GraphicElementType::HollowTriangle, _graphicsVector, positionA, positionB, positionC, color, size);
	}
}

void GraphicsDataJsonIO::ParseRectangles(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem)
{
	Vec3D positionA, positionB;
	Color color;
	float size;
	for (int i = 0; i < _jsonValue.size(); i++)
	{
		positionA = Vec3D(_jsonValue[i]["pontos"][0][0].asFloat(), _jsonValue[i]["pontos"][0][1].asFloat(), 0.0f);
		positionB = Vec3D(_jsonValue[i]["pontos"][1][0].asFloat(), _jsonValue[i]["pontos"][1][1].asFloat(), 0.0f);
		color = Color(
			(unsigned char)_jsonValue[i]["cor"][0].asInt(),
			(unsigned char)_jsonValue[i]["cor"][1].asInt(),
			(unsigned char)_jsonValue[i]["cor"][2].asInt(),
			255);
		size = _jsonValue[i]["esp"].asFloat() * m_pixelSize;
		positionA = (positionA + Vec3D(-0.5f, -0.5f, 0.0f)) * 2.0f;
		positionA.y *= -1;
		positionB = (positionB + Vec3D(-0.5f, -0.5f, 0.0f)) * 2.0f;
		positionB.y *= -1;
		_drawSystem.DrawRect(GraphicElementType::HollowRectangle, _graphicsVector, positionA, positionB, color, size);
	}
}

void GraphicsDataJsonIO::ParsePolys(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem)
{
	vector<Vec2D> vertices;
	Vec3D position;
	Color color;
	float size;
	for (int i = 0; i < _jsonValue.size(); i++)
	{
		for (int j = 0; j < _jsonValue[i]["pontos"].size(); j++)
		{
			position = Vec3D(_jsonValue[i]["pontos"][j][0].asFloat() - 0.5f, _jsonValue[i]["pontos"][j][1].asFloat() - 0.5f, 0.0f) * 2.0f;
			position.y *= -1;
			vertices.push_back(position);
		}
		color = Color(
			(unsigned char)_jsonValue[i]["cor"][0].asInt(),
			(unsigned char)_jsonValue[i]["cor"][1].asInt(),
			(unsigned char)_jsonValue[i]["cor"][2].asInt(),
			255);
		size = _jsonValue[i]["esp"].asFloat() * m_pixelSize;
		_drawSystem.DrawPoly(GraphicElementType::HollowPoly, _graphicsVector, Vec3Zero, color, vertices, size);
		vertices.clear();
	}
}


void GraphicsDataJsonIO::GetGraphicsFromJson(std::shared_ptr<IGeometryDataStructure> _outGraphics, string _filePath, DrawSystem& _drawSystem)
{
	Json::Value root;
	ifstream jsonFile(_filePath, ifstream::binary);

	jsonFile >> root;

	ParsePixels(_outGraphics, root["pontos"], _drawSystem);
	ParseLines(_outGraphics, root["retas"], _drawSystem);
	ParseCircles(_outGraphics, root["circulos"], _drawSystem);
	ParseTriangles(_outGraphics, root["triangulos"], _drawSystem);
	ParseRectangles(_outGraphics, root["retangulos"], _drawSystem);
	ParsePolys(_outGraphics, root["poligonos"], _drawSystem);

	jsonFile.close();	
}

void GraphicsDataJsonIO::WriteGraphicsToJson(string _newFilePath, std::shared_ptr<IGeometryDataStructure> _graphicsVector)
{
	Json::Value newRoot;
	Json::Value tempValue;
	std::ofstream outfile(_newFilePath, std::ofstream::binary);
	int vectorSize = _graphicsVector.get()->size();
	int numOfElements[6] = {0,0,0,0,0,0};
	vector<Vec2D> polyVertices;
	array<Vec2D, 3> triangleVertices;
	array<Vec2D, 2> rectVertices;
	array<Vec2D, 2> lineVertices;


	for (int i = 0; i < vectorSize; i++)
	{
		switch (_graphicsVector.get()->get_item(i).get()->GetGraphicElementType())
		{
		case GraphicElementType::Point:
			numOfElements[0]++;

			tempValue["nome"] = "ponto" + to_string(numOfElements[0]);
			tempValue["coord"][0] = (float)(((double)(_graphicsVector.get()->get_item(i).get()->GetPosition().x) / 2.0f) + 0.5f);
			tempValue["coord"][1] = (float)(((double)(_graphicsVector.get()->get_item(i).get()->GetPosition().y) * -1.0f / 2.0f) + 0.5f);
			tempValue["cor"][0] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.x;
			tempValue["cor"][1] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.y;
			tempValue["cor"][2] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.z;
			tempValue["esp"] = (int)fabsf(_graphicsVector.get()->get_item(i).get()->GetScale().y / m_pixelSize);
			newRoot["pontos"].append(tempValue);
			break;
		case GraphicElementType::Line:
			numOfElements[1]++;

			lineVertices = ((Line*)_graphicsVector.get()->get_item(i).get())->GetLineVertices();
			tempValue["nome"] = "reta" + to_string(numOfElements[1]);
			tempValue["pontos"][0][0] = (float)(((double)lineVertices[0].x / 2.0f) + 0.5f);
			tempValue["pontos"][0][1] = (float)(((double)lineVertices[0].y * -1.0f / 2.0f) + 0.5f);
			tempValue["pontos"][1][0] = (float)(((double)lineVertices[1].x / 2.0f) + 0.5f);
			tempValue["pontos"][1][1] = (float)(((double)lineVertices[1].y * -1.0f / 2.0f) + 0.5f);
			tempValue["cor"][0] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.x;
			tempValue["cor"][1] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.y;
			tempValue["cor"][2] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.z;
			tempValue["esp"] = (int)fabsf(((Line*)_graphicsVector.get()->get_item(i).get())->GetThickness() / m_pixelSize);
			newRoot["retas"].append(tempValue);
			break;
		case GraphicElementType::HollowRectangle:
			numOfElements[2]++;

			rectVertices = ((HollowRect*)_graphicsVector.get()->get_item(i).get())->GetRectVertices();
			tempValue["nome"] = "retangulo" + to_string(numOfElements[2]);
			tempValue["pontos"][0][0] = (float)(((double)rectVertices[0].x / 2.0f) + 0.5f);
			tempValue["pontos"][0][1] = (float)(((double)rectVertices[0].y * -1.0f / 2.0f) + 0.5f);
			tempValue["pontos"][1][0] = (float)(((double)rectVertices[1].x / 2.0f) + 0.5f);
			tempValue["pontos"][1][1] = (float)(((double)rectVertices[1].y * -1.0f / 2.0f) + 0.5f);
			tempValue["cor"][0] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.x;
			tempValue["cor"][1] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.y;
			tempValue["cor"][2] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.z;
			tempValue["esp"] = (int)fabsf(((HollowRect*)_graphicsVector.get()->get_item(i).get())->GetThickness() / m_pixelSize);
			newRoot["retangulos"].append(tempValue);
			break;
		case GraphicElementType::HollowTriangle:
			numOfElements[3]++;

			triangleVertices = ((HollowTriangle*)_graphicsVector.get()->get_item(i).get())->GetTriangleVertices();
			tempValue["nome"] = "triangulo" + to_string(numOfElements[3]);
			tempValue["pontos"][0][0] = (float)(((double)triangleVertices[0].x / 2.0f) + 0.5f);
			tempValue["pontos"][0][1] = (float)(((double)triangleVertices[0].y * -1.0f / 2.0f) + 0.5f);
			tempValue["pontos"][1][0] = (float)(((double)triangleVertices[1].x / 2.0f) + 0.5f);
			tempValue["pontos"][1][1] = (float)(((double)triangleVertices[1].y * -1.0f / 2.0f) + 0.5f);
			tempValue["pontos"][2][0] = (float)(((double)triangleVertices[2].x / 2.0f) + 0.5f);
			tempValue["pontos"][2][1] = (float)(((double)triangleVertices[2].y * -1.0f / 2.0f) + 0.5f);
			tempValue["cor"][0] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.x;
			tempValue["cor"][1] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.y;
			tempValue["cor"][2] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.z;
			tempValue["esp"] = (int)fabsf(((HollowTriangle*)_graphicsVector.get()->get_item(i).get())->GetThickness() / m_pixelSize);
			newRoot["triangulos"].append(tempValue);
			break;
		case GraphicElementType::Circle:
			numOfElements[4]++;

			tempValue["nome"] = "circulo" + to_string(numOfElements[4]);
			tempValue["centro"][0] = (float)(((double)(_graphicsVector.get()->get_item(i).get()->GetPosition().x) / 2.0f) + 0.5f);
			tempValue["centro"][1] = (float)(((double)(_graphicsVector.get()->get_item(i).get()->GetPosition().y) * -1.0f / 2.0f) + 0.5f);
			tempValue["cor"][0] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.x;
			tempValue["cor"][1] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.y;
			tempValue["cor"][2] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.z;
			tempValue["raio"] = _graphicsVector.get()->get_item(i).get()->GetScale().y;
			tempValue["esp"] = ((Circle*)_graphicsVector.get()->get_item(i).get())->GetThickness();
			newRoot["circulos"].append(tempValue);
			break;
		case GraphicElementType::HollowPoly:
			numOfElements[5]++;

			polyVertices = ((HollowPoly*)_graphicsVector.get()->get_item(i).get())->GetPolyLines();
			tempValue["nome"] = "poligono" + to_string(numOfElements[5]);

			for (int k = 0; k < polyVertices.size(); k++)
			{
				tempValue["pontos"][k][0] = (float)(((double)polyVertices[k].x / 2.0f) + 0.5f);
				tempValue["pontos"][k][1] = (float)(((double)polyVertices[k].y * -1.0f / 2.0f) + 0.5f);
			}
			tempValue["cor"][0] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.x;
			tempValue["cor"][1] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.y;
			tempValue["cor"][2] = _graphicsVector.get()->get_item(i).get()->GetGeometry()[0].color.z;
			tempValue["esp"] = (int)fabsf(((HollowPoly*)_graphicsVector.get()->get_item(i).get())->GetThickness() / m_pixelSize);
			newRoot["poligonos"].append(tempValue);
			break;
		}
		tempValue.clear();
	}




	outfile << newRoot << "\n";

	outfile.close();
}


GraphicsDataJsonIO::GraphicsDataJsonIO(float _pixelSize) : m_pixelSize(_pixelSize)
{
}