
#define _USE_MATH_DEFINES
#include "Editor3DControllerState.h"
#include "Input.h"
#include "Cube.h"

#define ROTATION_MULTI (M_PI / 45)
#define SCALE_MULTI 1.05f
#define CUBEPOINT_SIZE 0.01f

using namespace UIPrintComands;

void Editor3DControllerState::ChangeEditorState(Editor3DState _newState)
{
	m_uiManager->ClearUI();
	m_editorState = _newState;
	switch (_newState)
	{
	case Editor3DState::Translate:
		m_uiManager->PrintEditor3DTranslateText();
		break;
	case Editor3DState::OrbitPoint:
		m_orbitPointState = OrbitPointState::Initial;
		m_uiManager->PrintEditor3DOrbitText(m_orbitPointState);
		break;
	case Editor3DState::ScaleByPoint:
		m_scaleByPointState = ScaleByPointState::Initial;
		m_uiManager->PrintEditor3DScaleByPointText(m_scaleByPointState);
		break;
	case Editor3DState::Mirror:
		m_mirrorState = MirrorState::Initial;
		m_uiManager->PrintEditor3DMirrorText(m_mirrorState);
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void Editor3DControllerState::OnLeftMouseClick()
{
	Vec2D auxVec;
	Vec2D mouseClickPos;
	mouseClickPos = Input::GetNormalizedMousePos();
	mouseClickPos.y *= (float)HEIGHT / (float)WIDTH;
	switch (m_editorState)
	{
	case Editor3DState::Translate:
		m_selectedElement.get()->SetPosition(Vec3D(mouseClickPos, 0.0f));
		break;
	case Editor3DState::OrbitPoint:
		if (m_orbitPointState == OrbitPointState::Initial)
		{
			m_auxPosition = mouseClickPos;
			m_orbitPointState = OrbitPointState::PointSelected;
			m_appController->GetGeometry().get()->push_back(std::make_shared<BasicElements::Cube>(Vec4Red, Vec3D(mouseClickPos, 1.0f), CUBEPOINT_SIZE, GraphicElementType::Generic));
		}
		else
		{
			m_appController->GetGeometry().get()->pop_back();
			m_orbitPointState = OrbitPointState::Initial;
		}


		m_uiManager->PrintEditor3DOrbitText(m_orbitPointState);
		break;
	case Editor3DState::ScaleByPoint:
		if (m_scaleByPointState == ScaleByPointState::Initial)
		{
			m_auxPosition = mouseClickPos;
			m_scaleByPointState = ScaleByPointState::PointSelected;
			m_appController->GetGeometry().get()->push_back(std::make_shared<BasicElements::Cube>(Vec4Red, Vec3D(mouseClickPos, 1.0f), CUBEPOINT_SIZE, GraphicElementType::Generic));
		}
		else
		{
			m_appController->GetGeometry().get()->pop_back();
			m_scaleByPointState = ScaleByPointState::Initial;
		}

		m_uiManager->PrintEditor3DScaleByPointText(m_scaleByPointState);
		break;
	case Editor3DState::Mirror:
		if (m_mirrorState == MirrorState::Initial)
		{
			m_auxPosition = mouseClickPos;
			m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_auxPosition, 0.0f), Vec3D(mouseClickPos, 0.0f), Vec4Red, CUBEPOINT_SIZE);
			m_mirrorState = MirrorState::ChoosingSecondPoint;
		}
		else
		{
			auxVec = (m_selectedElement.get()->GetPosition() - m_auxPosition);

			auxVec.rotate(-(mouseClickPos - m_auxPosition).vectorAngle());
			m_selectedElement.get()->RotateGeometryOnZ(-(mouseClickPos - m_auxPosition).vectorAngle());

			auxVec.y *= -1.0f;
			m_selectedElement.get()->Scale(Vec3D(1.0f, -1.0f, 1.0f));

			m_selectedElement.get()->RotateGeometryOnZ((mouseClickPos - m_auxPosition).vectorAngle());
			auxVec.rotate((mouseClickPos - m_auxPosition).vectorAngle());

			m_selectedElement.get()->SetPosition(Vec3D(auxVec + m_auxPosition, 0.0f));

			m_appController->GetGeometry().get()->pop_back();
			m_mirrorState = MirrorState::Initial;
		}
		m_uiManager->PrintEditor3DMirrorText(m_mirrorState);
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void Editor3DControllerState::OnIncreaseValue()
{
	Vec2D auxVec;
	switch (m_editorState)
	{
	case Editor3DState::OrbitPoint:
		if (m_orbitPointState == OrbitPointState::PointSelected)
		{
			auxVec = ((m_selectedElement.get()->GetPosition()) - m_auxPosition);
			auxVec.rotate(ROTATION_MULTI);
			m_selectedElement.get()->RotateGeometryOnZ(ROTATION_MULTI);
			m_selectedElement.get()->SetPosition(Vec3D(m_auxPosition + auxVec, 0.0f));
		}
		break;
	case Editor3DState::ScaleByPoint:
		if (m_scaleByPointState == ScaleByPointState::PointSelected)
		{
			auxVec = ((m_selectedElement.get()->GetPosition()) - m_auxPosition);
			auxVec *= SCALE_MULTI;
			m_selectedElement.get()->Scale(Vec3One * SCALE_MULTI);
			m_selectedElement.get()->SetPosition(Vec3D(m_auxPosition + auxVec, 0.0f));
		}
		break;
	case Editor3DState::Mirror:
		break;
	default:
		break;
	}
}

void Editor3DControllerState::OnDecreaseValue()
{
	Vec2D auxVec;
	switch (m_editorState)
	{
	case Editor3DState::OrbitPoint:
		if (m_orbitPointState == OrbitPointState::PointSelected)
		{
			auxVec = ((m_selectedElement.get()->GetPosition()) - m_auxPosition);
			auxVec.rotate(-(ROTATION_MULTI));
			m_selectedElement.get()->RotateGeometryOnZ(-(ROTATION_MULTI));
			m_selectedElement.get()->SetPosition(Vec3D(m_auxPosition + auxVec, 0.0f));
		}
		break;
	case Editor3DState::ScaleByPoint:
		if (m_scaleByPointState == ScaleByPointState::PointSelected)
		{
			auxVec = ((m_selectedElement.get()->GetPosition()) - m_auxPosition);
			auxVec *= (2 - SCALE_MULTI);
			m_selectedElement.get()->Scale(Vec3One * (2 - SCALE_MULTI));
			m_selectedElement.get()->SetPosition(Vec3D(m_auxPosition + auxVec, 0.0f));
		}
		break;
	case Editor3DState::Mirror:
		break;
	default:
		break;
	}
}

void Editor3DControllerState::OnSelect()
{
}

void Editor3DControllerState::OnNoneSelected()
{
	Vec2D mouseClickPos;
	mouseClickPos = Input::GetNormalizedMousePos();
	mouseClickPos.y *= (float)HEIGHT / (float)WIDTH;
	if (m_editorState == Editor3DState::Mirror && m_mirrorState == MirrorState::ChoosingSecondPoint)
	{
		m_appController->GetGeometry().get()->pop_back();
		m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_auxPosition, 0.0f), Vec3D(mouseClickPos, 0.0f), Vec4Red, CUBEPOINT_SIZE);
	}
}

void Editor3DControllerState::Update()
{
	int newStateValue;
	if (Input::GetKeyDown(INPUT_KEY::L_MOUSE_BUTTON))
	{
		OnLeftMouseClick();
	}
	else if (Input::GetKeyDown(INPUT_KEY::ARROW_UP))
	{
		if (m_mirrorState == MirrorState::Initial &&
			m_scaleByPointState == ScaleByPointState::Initial &&
			m_orbitPointState == OrbitPointState::Initial)
		{
			newStateValue = ((int)m_editorState + 1) % (int)Editor3DState::Count;
			ChangeEditorState((Editor3DState)newStateValue);
		}
	}
	else if (Input::GetKeyDown(INPUT_KEY::ARROW_DOWN))
	{
		if (m_mirrorState == MirrorState::Initial &&
			m_scaleByPointState == ScaleByPointState::Initial &&
			m_orbitPointState == OrbitPointState::Initial)
		{
			newStateValue = ((int)m_editorState - 1);
			if (newStateValue < 0) newStateValue += (int)Editor3DState::Count;
			ChangeEditorState((Editor3DState)(newStateValue));
		}
	}
	else if (Input::GetKeyDown(INPUT_KEY::ARROW_RIGHT))
	{
		OnIncreaseValue();
	}
	else if (Input::GetKeyDown(INPUT_KEY::ARROW_LEFT))
	{
		OnDecreaseValue();
	}
	else if (Input::GetKey(INPUT_KEY::ARROW_RIGHT) && Input::GetKey(INPUT_KEY::SHIFT))
	{
		OnIncreaseValue();
	}
	else if (Input::GetKey(INPUT_KEY::ARROW_LEFT) && Input::GetKey(INPUT_KEY::SHIFT))
	{
		OnDecreaseValue();
	}
	else if (Input::GetKeyDown(INPUT_KEY::ESC) && 
		m_mirrorState == MirrorState::Initial &&
		m_scaleByPointState == ScaleByPointState::Initial &&
		m_orbitPointState == OrbitPointState::Initial)
	{
		m_appController->ChangeState(AppControllerState::MainMenu);
	}
	else
	{
		OnNoneSelected();
		//m_rotation = sinf(m_rotation + 0.0001f);
		//m_appController->GetGeometry().get()->get_item(0).get()->RotateGeometryOnY(m_rotation);
		//m_appController->GetGeometry().get()->get_item(0).get()->RotateGeometryOnX(m_rotation);
	}
}

void Editor3DControllerState::OnStateEnter()
{
	m_auxPosition = Vec2Zero;
	m_rotation = 0;
	m_appController->GetGeometry().get()->push_back(std::make_shared<BasicElements::Cube>(Vec4Blue, Vec3Zero, 0.06f, GraphicElementType::Generic));
	m_selectedElement = m_appController->GetGeometry().get()->get_item(0);
	m_appController->GetGeometry().get()->GetProjectionMatrix()->SetElement(1, 1, ((float)WIDTH / (float)HEIGHT));
	ChangeEditorState(Editor3DState::Translate);
}

void Editor3DControllerState::OnStateExit()
{
	m_uiManager->ClearUI();
	m_appController->GetGeometry().get()->clear();
}
