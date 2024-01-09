#pragma once

#include "DrawSystem.h"
#include "GraphicsDataJsonIO.h"
#include "UIManager.h"
#include "IGeometryDataStructure.h"

enum class AppControllerState
{
	MainMenu = 0,
	Editor = 1,
	Editor3D = 2
};

class IAppController
{
public:
	virtual void Update() = 0;
	virtual void ChangeState(AppControllerState _newState) = 0;
	virtual DrawSystem* GetDrawSystem() = 0;
	virtual GraphicsDataJsonIO* GetJsonIO() = 0;
	virtual UIManager* GetUIManager() = 0;
	virtual void QuitApp() = 0;
	virtual std::shared_ptr<IGeometryDataStructure> GetGeometry() = 0;
	virtual float GetPixelSize() = 0;
};