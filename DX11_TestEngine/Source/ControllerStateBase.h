#pragma once

#include "UIManager.h"
#include "IAppController.h"
#include "DrawSystem.h"
#include "GraphicsDataJsonIO.h"

class ControllerStateBase
{
protected:
	IAppController* m_appController;

	GraphicsDataJsonIO* m_jsonIO;
	UIManager* m_uiManager;
	DrawSystem* m_drawSystem;
public:
	ControllerStateBase(IAppController* _appController);
	/// <summary>
	/// Chamado todo frame
	/// </summary>
	virtual void Update() = 0;
	virtual void OnStateEnter() = 0;
	virtual void OnStateExit() = 0;
};

