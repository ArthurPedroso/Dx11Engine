#pragma once

#include "GraphicElement.h"
#include "DrawSystem.h"
#include "IGeometryDataStructure.h"
#include <vector>
#include <memory>
#include <string>
#include <json/json.h>

class GraphicsDataJsonIO
{
private:
	float m_pixelSize;

	void ParsePixels(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem);
	void ParseLines(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem);
	void ParseCircles(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem);
	void ParseTriangles(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem);
	void ParseRectangles(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem);
	void ParsePolys(std::shared_ptr<IGeometryDataStructure> _graphicsVector, Json::Value& _jsonValue, DrawSystem& _drawSystem);
public:
	GraphicsDataJsonIO(float _pixelSize);

	void GetGraphicsFromJson(std::shared_ptr<IGeometryDataStructure> _outGraphics, std::string _filePath, DrawSystem& _drawSystem);
	void WriteGraphicsToJson(std::string _newFilePath, std::shared_ptr<IGeometryDataStructure> _graphicsVector);
};

