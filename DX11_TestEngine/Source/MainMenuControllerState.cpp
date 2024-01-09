#include "MainMenuControllerState.h"
#include "Input.h"

void MainMenuControllerState::Update()
{
	if (Input::GetKeyDown(INPUT_KEY::NUM_1))
	{
		m_appController->ChangeState(AppControllerState::Editor);
	}
	else if (Input::GetKeyDown(INPUT_KEY::NUM_2))
	{
		m_appController->ChangeState(AppControllerState::Editor3D);
	}
	else if (Input::GetKeyDown(INPUT_KEY::NUM_3))
	{
		m_jsonIO->GetGraphicsFromJson(m_appController->GetGeometry(), "data.json", *m_drawSystem);
		m_appController->ChangeState(AppControllerState::Editor);
	}
	else if (Input::GetKeyDown(INPUT_KEY::ESC) || Input::GetKeyDown(INPUT_KEY::NUM_4))
	{
		m_appController->QuitApp();
	}
}

void MainMenuControllerState::OnStateEnter()
{
	m_uiManager->PrintMainMenu();
}

void MainMenuControllerState::OnStateExit()
{
	m_uiManager->ClearUI();
}
