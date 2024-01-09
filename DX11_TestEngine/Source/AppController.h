#pragma once
#include "ControllerStateBase.h"
#include "Editor2DControllerState.h"
#include "Editor3DControllerState.h"
#include "MainMenuControllerState.h"
#include "IAppController.h"
#include "DrawSystem.h"
#include "GraphicsDataJsonIO.h"
#include "IMainAppGeneralFunctions.h"

class AppController : IAppController
{
private:
	UIManager* m_uiManager;
	GraphicsDataJsonIO* m_jsonIO;
	DrawSystem* m_drawSystem;
	IMainAppGeneralFunctions* m_mainAppGeneralFunctions;

	//States:
	ControllerStateBase* m_currentState;
	Editor2DControllerState m_editorState;
	Editor3DControllerState m_editor3DState;
	MainMenuControllerState m_mainMenuState;
public:
	AppController(UIManager* _uiManager, DrawSystem* _drawSystem, GraphicsDataJsonIO* _jsonIO, IMainAppGeneralFunctions* _quitInterface);

	virtual void Update() override;
	virtual void ChangeState(AppControllerState _newState) override;
	virtual DrawSystem* GetDrawSystem() override;
	virtual GraphicsDataJsonIO* GetJsonIO() override;
	virtual UIManager* GetUIManager() override;
	virtual void QuitApp() override;
	virtual std::shared_ptr<IGeometryDataStructure> GetGeometry() override;
	virtual float GetPixelSize() override;
};

