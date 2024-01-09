#pragma once

#include "GraphicElement.h"
#include <vector>
#include <memory>

class IMainAppGeneralFunctions
{
public:
	virtual void QuitApp() = 0;
	virtual std::shared_ptr<IGeometryDataStructure> GetGeometry() = 0;
	virtual float GetPixelSize() = 0;
};