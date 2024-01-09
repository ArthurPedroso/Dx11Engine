#pragma once

#include "ControllerStateBase.h"
#include <vector>

class Editor2DControllerState : public ControllerStateBase
{
private:
	enum class Editor2DState : int
	{
		PointState = 0,
		CircleState = 1,
		LineState = 2,
		RectState = 3,
		TriangleState = 4,
		PolyState = 5,
		SelectColorState = 6,
		SelectThicknessState = 7,
		Count = 8
	};

	Editor2DState m_editor2DState;
	UIPrintComands::DrawCircleState m_drawCircleState;
	UIPrintComands::DrawLineState m_drawLineState;
	UIPrintComands::DrawPolyState m_drawPolyState;
	UIPrintComands::DrawRectState m_drawRectState;
	UIPrintComands::DrawTriangleState m_drawTriangleState;
	UIPrintComands::SelectColorState m_selectColorState;
	std::vector<Vector2::Vec2D> m_drawingBuffer;

	Vector4::VecByte4D m_selectedColor;
	int m_selectedThickness;

	void ChangeEditorState(Editor2DState _newState);
	
	void DrawPoint();
	void DrawCircle();
	void DrawLine();
	void DrawPoly();
	void ClosePoly();
	void DrawRect();
	void DrawTriangle();
	void SelectColor();
	void SelectThickness();

	void OnLeftMouseClick();
	void OnIncreaseValue();
	void OnDecreaseValue();
	void OnSelect();
	void OnNoneSelected();
public:
	virtual void Update() override;
	virtual void OnStateEnter() override;
	virtual void OnStateExit() override;

	//Especifica que queremos usar o construtor da classe pai
	using ControllerStateBase::ControllerStateBase;
};

