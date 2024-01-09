#include "MainApp.h"
#include "CustomWinInclude.h"
#include "Common.h"
#include "Cube.h"
#include "Quad.h"
#include "Input.h"
#include "VectorDataStructure.h"
#include <string>
#include <iterator>
#include <string>
#include <chrono>


using namespace std::chrono;

void MainApp::ComputeFrame()
{
	if(!m_mainWindow.WindowMinimized())
		m_mainWindow.GetGraphics().ShipFrame(m_graphicElements);
}

void MainApp::DrawText(LPCWSTR _text, Vector2::Vec2D _pos, float _size, Vector4::Vec4D _color)
{
	m_mainWindow.GetGraphics().DrawText(_text, _pos, _size, _color);
	
}

void MainApp::ClearText()
{
	m_mainWindow.GetGraphics().ClearText();
}

int MainApp::Run()
{
	int quitCode;
	float x = 0;
	//m_graphicElements.get()->push_back(std::make_shared<BasicElements::Cube>(Vec4Blue, Vec3Zero, m_pixelSize * 100, GraphicElementType::Generic));
	while (!Window::ComputeMessages(quitCode) && !m_quitApp)
	{
		ComputeFrame();
		m_controller.Update();
		//x = sinf(x + 0.0001f);
		//m_graphicElements.get()->get_item(0).get()->RotateGeometryOnY(x);
		//m_graphicElements.get()->get_item(0).get()->RotateGeometryOnX(x);
	}
	return quitCode;
	/*
	steady_clock::time_point begin;
	steady_clock::time_point end;
	std::wstring drawString;
	int quitCode;
	int divis = 0;
	int menuState = -1;
	int timeCalcAux;
	double divisionTime = 0.0;
	bool countTime = false;
	bool usingSoftware = true;

	while (!Window::ComputeMessages(quitCode))
	{
		ComputeFrame();
		ClearText();

		if (menuState == -1)
		{
			drawString = L"Selecione o desenho:\n 0: Ler Json";
			drawString = drawString.append(L"\n\n Tecle ESPACO para mudar o sistema de renderizacao");
			drawString = drawString.append(L"\n Sistema atual de renderizacao = "); 
			drawString = drawString.append(usingSoftware ? L"Software" : L"Hardware");
			
			DrawText(
				drawString.c_str(),
				Vector2::Vec2D(WIDTH / 2, 40), 40, Vec4One);
			if (Input::GetKeyDown(INPUT_KEY::ESC))
			{
				break;
			}
			else if (Input::GetKeyDown(INPUT_KEY::SPACE))
			{
				usingSoftware = !usingSoftware;
				if (usingSoftware)
					m_drawSys = std::make_unique<DrawHardware>(m_pixelSize);
				else
					m_drawSys = std::make_unique<DrawHardware>(m_pixelSize);
			}
			else if (Input::GetKeyDown(INPUT_KEY::NUM_0))
			{			
				m_graphicElements = m_jsonIO.GetGraphicsFromJson("Source\\test.json", *m_drawSys.get());
				menuState = 0;
			}
		}
		else
		{
			if (countTime)
			{
				end = steady_clock::now();
				divisionTime = duration_cast<milliseconds>(end - begin).count();
				countTime = false;
			}

			drawString = L"Divis = " + std::to_wstring(divis);
			drawString = drawString.append(L" Tempo de execucao = ");
			drawString = drawString.append(std::to_wstring((int)divisionTime / 1000) + L".");

			timeCalcAux = (int)divisionTime % 1000;
			if (timeCalcAux < 10) drawString = drawString.append(L"00");
			else if (timeCalcAux < 100) drawString = drawString.append(L"0");
			drawString = drawString.append(std::to_wstring(timeCalcAux) + L" s");

			DrawText(drawString.c_str(), Vector2::Vec2D(WIDTH / 2, HEIGHT - 40), 40, Vec4One);
			DrawText(L"Pressione ESC para sair", Vector2::Vec2D(WIDTH / 2, 20), 40, Vec4One);

			if (Input::GetKeyDown(INPUT_KEY::ESC))
			{
				menuState = -1;
				divis = 0;
				m_jsonIO.WriteGraphicsToJson("new.json", m_graphicElements);
				m_drawSys = std::make_unique<DrawHardware>(m_pixelSize);
				usingSoftware = true;
				m_graphicElements.get()->clear();
			}
		}
	}

	return quitCode;
	*/
}

void MainApp::QuitApp()
{
	m_quitApp = true;
}

std::shared_ptr<IGeometryDataStructure> MainApp::GetGeometry()
{
	return m_graphicElements;
}

float MainApp::GetPixelSize()
{
	return m_pixelSize;
}

MainApp::MainApp(float _pixelSize) : m_quitApp(false), m_mainWindow(WIDTH, HEIGHT, L"Dx11_Test"), m_pixelSize(_pixelSize), m_jsonIO(_pixelSize), m_drawSystem(_pixelSize),
									m_UIManager(this), m_controller(&m_UIManager, &m_drawSystem, &m_jsonIO, this)
{
	m_graphicElements = std::make_shared<VectorDataStructure>();
	m_controller.ChangeState(AppControllerState::MainMenu);
	
	//m_graphicElements.get()->push_back(std::make_shared<BasicElements::Cube>(Vec4Blue, Vec3Zero, m_pixelSize * 100, GraphicElementType::Generic));
	//m_graphicElements.get()->push_back(std::make_shared<BasicElements::Quad>(Vec4Blue, Vec3Forward * -0.00001f, m_pixelSize * 100, GraphicElementType::Generic));
	//m_graphicElements = m_jsonIO.GetGraphicsFromJson("newBigTest.json", *m_drawSys.get());
	
	//m_UIManager.PrintMainMenu();

	//m_drawSys.get()->DrawCircle(GraphicElementType::Circle, m_graphicElements, Vec3One, 0.2, Vec4Blue);
	//m_drawSys.get()->DrawPixel(GraphicElementType::Point, m_graphicElements, Vec3One * 0.99f, Vec4Blue, 0.1f);
	//m_drawSys.get()->DrawLine(GraphicElementType::Line, m_graphicElements, Vec3D(0.5f, 0.4f, 0.0f), Vec3D(-0.4f, -0.4f, 0.0f), Vec4Green, _pixelSize);
	//m_drawSys.get()->DrawRect(GraphicElementType::HollowRectangle, m_graphicElements, Vec3D(0, 0, 0.0f), Vec3D(1, 1, 0.0f), Vec4One, _pixelSize);
	//m_drawSys.get()->DrawTriangle(GraphicElementType::HollowTriangle, m_graphicElements, Vec3D(1, -1, 0.0f), Vec3D(0, -0.1f, 0.0f), Vec3D(1, -0.1f, 0.0f), Vec4Red, _pixelSize);
	//m_jsonIO.WriteGraphicsToJson("newBigTest.json", m_graphicElements);
	//(*m_graphicElements.get())[m_graphicElements.get()->size() - 1].get()->SetPosition(Vec3D(1, 1, 0.0f));
	//m_drawSys.get()->DrawRect(m_graphicElements, Vec3D(0, 0, 0.0f), Vec3D(-0.5f , 0.5f, 0.0f), Vec4One);
	//m_drawSys.get()->DrawTriangle(m_graphicElements, Vec3D(-0.5f, 0, 0.0f), Vec4Blue, 0.1f);
	//m_graphicElements = GraphicsDataJsonIO().GetGraphicsFromJson("Source\\test.json");
	//m_graphicElements.get()->push_back(std::make_shared<PrimitiveGeometry::Quad>(Vector4::Vec4One, 0.0f)); //gambiarra para forcar o DX11 a funcionar
	//(*m_graphicElements.get())[0].get()->ApplyScale(Vector3::Vec3One * 0.2f);
	//(*m_graphicElements.get())[0].get()->SetPosition(Vector3::Vec3One * 0.6f);
	//(*m_graphicElements.get())[0].get()->RotateGeometry(0.8f);
}
