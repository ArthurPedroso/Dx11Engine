#include "Editor2DControllerState.h"
#include "Input.h"
#include <exception>

using namespace UIPrintComands;

void Editor2DControllerState::DrawPoint()
{
	m_drawSystem->DrawPixel(GraphicElementType::Point, m_appController->GetGeometry(), Vec3D(Input::GetNormalizedMousePos(), 0.0f), m_selectedColor, m_appController->GetPixelSize() * m_selectedThickness);
}

void Editor2DControllerState::DrawCircle()
{
	float circleRadius;
	switch (m_drawCircleState)
	{
	case DrawCircleState::Initial:
		m_drawingBuffer.push_back(Input::GetNormalizedMousePos());
		circleRadius = (Input::GetNormalizedMousePos() - m_drawingBuffer[0]).magnitude();
		m_drawSystem->DrawCircle(GraphicElementType::Circle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), circleRadius, m_selectedColor, m_selectedThickness);
		m_drawCircleState = DrawCircleState::ChoosingRadius;
		break;
	case DrawCircleState::ChoosingRadius:
		m_appController->GetGeometry().get()->pop_back();
		circleRadius = (Input::GetNormalizedMousePos() - m_drawingBuffer[0]).magnitude();
		m_drawSystem->DrawCircle(GraphicElementType::Circle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), circleRadius, m_selectedColor, m_selectedThickness);
		m_drawCircleState = DrawCircleState::Initial;
		m_drawingBuffer.clear();
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void Editor2DControllerState::DrawLine()
{
	switch (m_drawLineState)
	{
	case DrawLineState::Initial:
		m_drawingBuffer.push_back(Input::GetNormalizedMousePos());
		m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawLineState = DrawLineState::ChoosingSecondPoint;
		break;
	case DrawLineState::ChoosingSecondPoint:
		m_appController->GetGeometry().get()->pop_back();
		m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawLineState = DrawLineState::Initial;
		m_drawingBuffer.clear();
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void Editor2DControllerState::DrawRect()
{
	switch (m_drawRectState)
	{
	case DrawRectState::Initial:
		m_drawingBuffer.push_back(Input::GetNormalizedMousePos());
		m_drawSystem->DrawRect(GraphicElementType::HollowRectangle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawRectState = DrawRectState::ChoosingSecondPoint;
		break;
	case DrawRectState::ChoosingSecondPoint:
		m_appController->GetGeometry().get()->pop_back();
		m_drawSystem->DrawRect(GraphicElementType::HollowRectangle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawRectState = DrawRectState::Initial;
		m_drawingBuffer.clear();
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void Editor2DControllerState::DrawPoly()
{
	switch (m_drawPolyState)
	{
	case DrawPolyState::Initial:
		m_drawingBuffer.push_back(Input::GetNormalizedMousePos());
		m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawPolyState = DrawPolyState::ChoosingSecondPoint;
		break;
	case DrawPolyState::ChoosingSecondPoint:
		m_drawingBuffer.push_back(Input::GetNormalizedMousePos());
		m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[m_drawingBuffer.size() - 1], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawPolyState = DrawPolyState::ChoosingNextPoint;
		break;
	case DrawPolyState::ChoosingNextPoint:
		m_appController->GetGeometry().get()->pop_back();
		m_appController->GetGeometry().get()->pop_back();
		m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[m_drawingBuffer.size() - 1], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawingBuffer.push_back(Input::GetNormalizedMousePos());
		m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[m_drawingBuffer.size() - 1], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void Editor2DControllerState::ClosePoly()
{
	for(int i = 0; i <= m_drawingBuffer.size(); i++)
	{
		m_appController->GetGeometry().get()->pop_back();
	}
	m_drawSystem->DrawPoly(GraphicElementType::HollowPoly, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), m_selectedColor,
		m_drawingBuffer, m_selectedThickness * m_appController->GetPixelSize());
	m_drawingBuffer.clear();
	m_drawPolyState = DrawPolyState::Initial;
}

void Editor2DControllerState::DrawTriangle()
{
	switch (m_drawTriangleState)
	{
	case DrawTriangleState::Initial:
		m_drawingBuffer.push_back(Input::GetNormalizedMousePos());
		m_drawSystem->DrawLine(GraphicElementType::HollowTriangle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawTriangleState = DrawTriangleState::ChoosingSecondPoint;
		break;
	case DrawTriangleState::ChoosingSecondPoint:
		m_appController->GetGeometry().get()->pop_back();
		m_drawSystem->DrawLine(GraphicElementType::HollowTriangle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
			m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawingBuffer.push_back(Input::GetNormalizedMousePos());
		m_drawTriangleState = DrawTriangleState::ChoosingThirdPoint;
		break;
	case DrawTriangleState::ChoosingThirdPoint:
		m_appController->GetGeometry().get()->pop_back();
		m_drawSystem->DrawTriangle(GraphicElementType::HollowTriangle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(m_drawingBuffer[1], 0.0f), 
			Vec3D(Input::GetNormalizedMousePos(), 0.0f), m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
		m_drawingBuffer.push_back(Input::GetNormalizedMousePos());
		m_drawingBuffer.clear();
		m_drawTriangleState = DrawTriangleState::Initial;
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void Editor2DControllerState::SelectColor()
{
}

void Editor2DControllerState::SelectThickness()
{
}


void Editor2DControllerState::ChangeEditorState(Editor2DState _newState)
{
	m_uiManager->ClearUI();
	m_editor2DState = _newState;
	switch (_newState)
	{
	case Editor2DState::PointState:
		m_uiManager->PrintEditorDrawPointMode();
		break;
	case Editor2DState::CircleState:
		m_drawCircleState = DrawCircleState::Initial;
		m_uiManager->PrintEditorDrawCircleMode(m_drawCircleState);
		break;
	case Editor2DState::LineState:
		m_drawLineState = DrawLineState::Initial;
		m_uiManager->PrintEditorDrawLineMode(m_drawLineState);
		break;
	case Editor2DState::RectState:
		m_drawRectState = DrawRectState::Initial;
		m_uiManager->PrintEditorDrawRectMode(m_drawRectState);
		break;
	case Editor2DState::PolyState:
		m_drawPolyState = DrawPolyState::Initial;
		m_uiManager->PrintEditorDrawPolyMode(m_drawPolyState);
		break;
	case Editor2DState::TriangleState:
		m_drawTriangleState = DrawTriangleState::Initial;
		m_uiManager->PrintEditorDrawTriangleMode(m_drawTriangleState);
		break;
	case Editor2DState::SelectColorState:
		m_selectColorState = SelectColorState::Initial;
		m_uiManager->PrintEditorSelectColorMode(m_selectColorState, m_selectedColor.x);
		break;
	case Editor2DState::SelectThicknessState:
		m_uiManager->PrintEditorSelectThicknessMode(m_selectedThickness);
		break;
	default:
		throw std::bad_exception();
		break;
	}
}


void Editor2DControllerState::OnLeftMouseClick()
{
	switch (m_editor2DState)
	{
	case Editor2DState::PointState:
		DrawPoint();
		break;
	case Editor2DState::CircleState:
		DrawCircle();
		break;
	case Editor2DState::LineState:
		DrawLine();
		break;
	case Editor2DState::RectState:
		DrawRect();
		break;
	case Editor2DState::PolyState:
		DrawPoly();
		break;
	case Editor2DState::TriangleState:
		DrawTriangle();
		break;
	case Editor2DState::SelectColorState:
		break;
	case Editor2DState::SelectThicknessState:
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void Editor2DControllerState::OnIncreaseValue()
{
	switch (m_editor2DState)
	{
	case Editor2DState::SelectColorState:
		switch (m_selectColorState)
		{
		case SelectColorState::Initial:
			m_selectedColor.x = (m_selectedColor.x + 1) % 256;
			m_uiManager->PrintEditorSelectColorMode(m_selectColorState, m_selectedColor.x);
			break;
		case SelectColorState::ChoosingGreen:
			m_selectedColor.y = (m_selectedColor.y + 1) % 256;
			m_uiManager->PrintEditorSelectColorMode(m_selectColorState, m_selectedColor.y);
			break;
		case SelectColorState::ChoosingBlue:
			m_selectedColor.z = (m_selectedColor.z + 1) % 256;
			m_uiManager->PrintEditorSelectColorMode(m_selectColorState, m_selectedColor.z);
			break;
		default:
			throw std::bad_exception();
			break;
		}
		break;
	case Editor2DState::SelectThicknessState:
		m_selectedThickness = (m_selectedThickness + 1) % 501;
		m_uiManager->PrintEditorSelectThicknessMode(m_selectedThickness);
		break;
	default:
		break;
	}
}

void Editor2DControllerState::OnDecreaseValue()
{
	switch (m_editor2DState)
	{
	case Editor2DState::SelectColorState:
		switch (m_selectColorState)
		{
		case SelectColorState::Initial:
			m_selectedColor.x = (m_selectedColor.x - 1);
			if (m_selectedColor.x < 0) m_selectedColor.x = 255;
			m_uiManager->PrintEditorSelectColorMode(m_selectColorState, m_selectedColor.x);
			break;
		case SelectColorState::ChoosingGreen:
			m_selectedColor.y = (m_selectedColor.y - 1);
			if (m_selectedColor.y < 0) m_selectedColor.y = 255;
			m_uiManager->PrintEditorSelectColorMode(m_selectColorState, m_selectedColor.y);
			break;
		case SelectColorState::ChoosingBlue:
			m_selectedColor.z = (m_selectedColor.z - 1);
			if (m_selectedColor.z < 0) m_selectedColor.z = 255;
			m_uiManager->PrintEditorSelectColorMode(m_selectColorState, m_selectedColor.z);
			break;
		default:
			throw std::bad_exception();
			break;
		}
		break;
	case Editor2DState::SelectThicknessState:
		m_selectedThickness = (m_selectedThickness - 1);
		if (m_selectedThickness < 0) m_selectedThickness = 500;
		m_uiManager->PrintEditorSelectThicknessMode(m_selectedThickness);
		break;
	default:
		break;
	}
}
void Editor2DControllerState::OnSelect()
{
	switch (m_editor2DState)
	{
	case Editor2DState::SelectColorState:
		m_selectColorState = (SelectColorState)(((int)m_selectColorState + 1) % (int)SelectColorState::Count);
		switch (m_selectColorState)
		{
		case SelectColorState::Initial:
			m_uiManager->PrintEditorSelectColorMode(m_selectColorState, m_selectedColor.x);
			break;
		case SelectColorState::ChoosingGreen:
			m_uiManager->PrintEditorSelectColorMode(m_selectColorState, m_selectedColor.y);
			break;
		case SelectColorState::ChoosingBlue:
			m_uiManager->PrintEditorSelectColorMode(m_selectColorState, m_selectedColor.z);
			break;
		}
		break;
	default:
		break;
	}
}
void Editor2DControllerState::OnNoneSelected()
{
	float circleRadius;
	switch (m_editor2DState)
	{
	case Editor2DState::PointState:
		break;
	case Editor2DState::CircleState:
		switch (m_drawCircleState)
		{
		case DrawCircleState::Initial:
			break;
		case DrawCircleState::ChoosingRadius:
			m_appController->GetGeometry().get()->pop_back();
			circleRadius = (Input::GetNormalizedMousePos() - m_drawingBuffer[0]).magnitude();
			m_drawSystem->DrawCircle(GraphicElementType::Circle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), circleRadius, m_selectedColor, m_selectedThickness);
			break;
		default:
			throw std::bad_exception();
			break;
		}
		break;
	case Editor2DState::LineState:
		switch (m_drawLineState)
		{
		case DrawLineState::Initial:
			break;
		case DrawLineState::ChoosingSecondPoint:
			m_appController->GetGeometry().get()->pop_back();
			m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
				m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
			break;
		default:
			throw std::bad_exception();
			break;
		}
		break;
	case Editor2DState::RectState:
		switch (m_drawRectState)
		{
		case DrawRectState::Initial:
			break;
		case DrawRectState::ChoosingSecondPoint:
			m_appController->GetGeometry().get()->pop_back();
			m_drawSystem->DrawRect(GraphicElementType::HollowRectangle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
				m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
			break;
		default:
			throw std::bad_exception();
			break;
		}
		break;
	case Editor2DState::PolyState:
		switch (m_drawPolyState)
		{
		case DrawPolyState::Initial:
			break;
		case DrawPolyState::ChoosingSecondPoint:
			m_appController->GetGeometry().get()->pop_back();
			m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
				m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
			break;
		case DrawPolyState::ChoosingNextPoint:
			m_appController->GetGeometry().get()->pop_back();
			m_appController->GetGeometry().get()->pop_back();
			m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
				m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
			m_drawSystem->DrawLine(GraphicElementType::Line, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[m_drawingBuffer.size() - 1], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
				m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
			break;
		default:
			throw std::bad_exception();
			break;
		}
		break;
	case Editor2DState::TriangleState:

		switch (m_drawTriangleState)
		{
		case DrawTriangleState::Initial:
			break;
		case DrawTriangleState::ChoosingSecondPoint:
			m_appController->GetGeometry().get()->pop_back();
			m_drawSystem->DrawLine(GraphicElementType::HollowTriangle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(Input::GetNormalizedMousePos(), 0.0f),
				m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
			break;
		case DrawTriangleState::ChoosingThirdPoint:
			m_appController->GetGeometry().get()->pop_back();
			m_drawSystem->DrawTriangle(GraphicElementType::HollowTriangle, m_appController->GetGeometry(), Vec3D(m_drawingBuffer[0], 0.0f), Vec3D(m_drawingBuffer[1], 0.0f),
				Vec3D(Input::GetNormalizedMousePos(), 0.0f), m_selectedColor, m_selectedThickness * m_appController->GetPixelSize());
			break;
		default:
			throw std::bad_exception();
			break;
		}
		break;
	case Editor2DState::SelectColorState:
		break;
	case Editor2DState::SelectThicknessState:
		break;
	default:
		break;
	}
}
//PUBLIC:
void Editor2DControllerState::Update()
{
	int newEditorStateValue;


	
	if(Input::GetKeyDown(INPUT_KEY::L_MOUSE_BUTTON))
	{
		OnLeftMouseClick();
	}
	else if (Input::GetKeyDown(INPUT_KEY::R_MOUSE_BUTTON) && m_editor2DState == Editor2DState::PolyState && m_drawPolyState == DrawPolyState::ChoosingNextPoint)
	{
		ClosePoly();
	}
	else if (Input::GetKeyDown(INPUT_KEY::ARROW_UP))
	{
		newEditorStateValue = ((int)m_editor2DState + 1) % (int)Editor2DState::Count;
		ChangeEditorState((Editor2DState)newEditorStateValue);
	}
	else if (Input::GetKeyDown(INPUT_KEY::ARROW_DOWN))
	{
		newEditorStateValue = ((int)m_editor2DState - 1);
		if (newEditorStateValue < 0) newEditorStateValue += (int)Editor2DState::Count;
		ChangeEditorState((Editor2DState)(newEditorStateValue));
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
	else if (Input::GetKeyDown(INPUT_KEY::SPACE))
	{
		OnSelect();
	}
	else if (Input::GetKey(INPUT_KEY::CTRL) && Input::GetKeyDown(INPUT_KEY::Z))
	{
		if(m_appController->GetGeometry().get()->size() > 0)
			m_appController->GetGeometry().get()->pop_back();
	}
	else if (Input::GetKeyDown(INPUT_KEY::ESC) &&
		m_drawCircleState == DrawCircleState::Initial &&
		m_drawLineState == DrawLineState::Initial &&
		m_drawPolyState == DrawPolyState::Initial &&
		m_drawRectState == DrawRectState::Initial &&
		m_drawTriangleState == DrawTriangleState::Initial &&
		m_selectColorState == SelectColorState::Initial)
	{
		m_jsonIO->WriteGraphicsToJson("data.json", m_appController->GetGeometry());
		m_appController->ChangeState(AppControllerState::MainMenu);
	}
	else
	{
		OnNoneSelected();
	}
}

void Editor2DControllerState::OnStateEnter()
{
	m_selectedThickness = 1;
	m_selectedColor = Vec4One;
	m_drawingBuffer.clear();

	m_appController->GetGeometry().get()->GetProjectionMatrix()->SetElement(1, 1, 1);
	ChangeEditorState(Editor2DState::PointState);
}

void Editor2DControllerState::OnStateExit()
{
	m_uiManager->ClearUI();
	m_appController->GetGeometry().get()->clear();
	m_drawingBuffer.clear();
}