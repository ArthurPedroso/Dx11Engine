#pragma once

#include "Window.h"
#include "GraphicElement.h"
#include "DrawHardware.h"
#include "GraphicsDataJsonIO.h"
#include "AppController.h"
#include "UIManager.h"
#include "IUIText.h"
#include "IMainAppGeneralFunctions.h"
#include "IGeometryDataStructure.h"
#include <vector>
#include <memory>

class MainApp : public IUIText, public IMainAppGeneralFunctions
{
private:
	//Fields:
	AppController m_controller;
	UIManager m_UIManager;
	GraphicsDataJsonIO m_jsonIO;
	Window m_mainWindow;
	DrawHardware m_drawSystem;
	//std::shared_ptr<std::vector<std::shared_ptr<GraphicElement>>> m_graphicElements;
	std::shared_ptr<IGeometryDataStructure> m_graphicElements;

	float m_pixelSize;
	bool m_quitApp;
	
	//Methods:
	void ComputeFrame();
	virtual void DrawText(LPCWSTR _text, Vector2::Vec2D _pos, float _size, Vector4::Vec4D _color) override;
	virtual void ClearText() override;
public:
	int Run();
	//Constructor
	MainApp(float _pixelSize);
	virtual void QuitApp() override;
	virtual std::shared_ptr<IGeometryDataStructure> GetGeometry() override;
	virtual float GetPixelSize() override;
};

