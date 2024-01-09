#include "AppController.h"
#include <exception>

AppController::AppController(UIManager* _uiManager, DrawSystem* _drawSystem, GraphicsDataJsonIO* _jsonIO, IMainAppGeneralFunctions* _quitInterface) :
	m_mainAppGeneralFunctions(_quitInterface),
	m_uiManager(_uiManager),
	m_drawSystem(_drawSystem),
	m_jsonIO(_jsonIO),
	m_editorState(this), 
	m_editor3DState(this),
	m_mainMenuState(this), 
	m_currentState(nullptr)
{
}

void AppController::Update()
{
	m_currentState->Update();
}

void AppController::ChangeState(AppControllerState _newState)
{
	if(m_currentState != nullptr) m_currentState->OnStateExit();
	switch (_newState)
	{
	case AppControllerState::MainMenu:
		m_currentState = &m_mainMenuState;
		break;
	case AppControllerState::Editor:
		m_currentState = &m_editorState;
		break;
	case AppControllerState::Editor3D:
		m_currentState = &m_editor3DState;
		break;
	default:
		throw std::bad_exception();
		break;
	}
	m_currentState->OnStateEnter();
}

DrawSystem* AppController::GetDrawSystem()
{
	return m_drawSystem;
}

GraphicsDataJsonIO* AppController::GetJsonIO()
{
	return m_jsonIO;
}

UIManager* AppController::GetUIManager()
{
	return m_uiManager;
}

void AppController::QuitApp()
{
	m_mainAppGeneralFunctions->QuitApp();
}

std::shared_ptr<IGeometryDataStructure> AppController::GetGeometry()
{
	return m_mainAppGeneralFunctions->GetGeometry();
}

float AppController::GetPixelSize()
{
	return m_mainAppGeneralFunctions->GetPixelSize();
}
