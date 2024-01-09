#pragma once

#include "CustomWinInclude.h"
#include "Vectors.h"
#include "IUIText.h"
#include <string>
#include <vector>

namespace UIPrintComands
{
	enum class DrawCircleState : int
	{
		Initial = 0,
		ChoosingRadius = 1
	};
	enum class DrawLineState : int
	{
		Initial = 0,
		ChoosingSecondPoint = 1
	};
	enum class DrawRectState : int
	{
		Initial = 0,
		ChoosingSecondPoint = 1
	};
	enum class DrawTriangleState : int
	{
		Initial = 0,
		ChoosingSecondPoint = 1,
		ChoosingThirdPoint = 2
	};
	enum class DrawPolyState : int
	{
		Initial = 0,
		ChoosingSecondPoint = 1,
		ChoosingNextPoint
	};
	enum class SelectColorState : int
	{
		Initial = 0,
		ChoosingGreen = 1,
		ChoosingBlue = 2,
		Count = 3
	};


	enum class OrbitPointState : int
	{
		Initial = 0,
		PointSelected = 1
	};
	enum class ScaleByPointState : int
	{
		Initial = 0,
		PointSelected = 1
	};
	enum class MirrorState : int
	{
		Initial = 0,
		ChoosingSecondPoint = 1
	};
}

class UIManager
{
private:
	IUIText* m_textApi;
	std::vector<std::wstring> m_textsBuffers;

public:
	UIManager(IUIText* _textApi);

	void ClearUI();

	void PrintMainMenu();

	void PrintEditorDrawPointMode();
	void PrintEditorDrawCircleMode(UIPrintComands::DrawCircleState _drawCircleState);
	void PrintEditorDrawLineMode(UIPrintComands::DrawLineState _drawLineState);
	void PrintEditorDrawRectMode(UIPrintComands::DrawRectState _drawRectState);
	void PrintEditorDrawTriangleMode(UIPrintComands::DrawTriangleState _drawTriangleState);
	void PrintEditorDrawPolyMode(UIPrintComands::DrawPolyState _drawPolyState);

	void PrintEditorSelectColorMode(UIPrintComands::SelectColorState _selectColorState, int _currentColor);
	void PrintEditorSelectThicknessMode(int _thicknessValue);


	void PrintEditor3DTranslateText();
	void PrintEditor3DOrbitText(UIPrintComands::OrbitPointState _orbitPointState);
	void PrintEditor3DScaleByPointText(UIPrintComands::ScaleByPointState _scaleByPointState);
	void PrintEditor3DMirrorText(UIPrintComands::MirrorState _mirrorState);
};

