#include "UIManager.h"
#include "Common.h"
#include <exception>
#include <string>

using namespace Vector2;
using namespace Vector3;
using namespace Vector4;
using namespace UIPrintComands;

UIManager::UIManager(IUIText* _textApi) : m_textApi(_textApi), m_textsBuffers()
{
}

void UIManager::ClearUI()
{
	m_textsBuffers.clear();
	m_textApi->ClearText();
}

void UIManager::PrintMainMenu()
{
	m_textsBuffers.push_back(L"Menu Principal\n\n\n");
	m_textsBuffers[0] = m_textsBuffers[0].append(L"1.Editor de formas 2D\n");
	m_textsBuffers[0] = m_textsBuffers[0].append(L"2.Editor de formas 3D\n");
	m_textsBuffers[0] = m_textsBuffers[0].append(L"3.Carregar arquivo \"data.json\" com formas 2D\n");
	m_textsBuffers[0] = m_textsBuffers[0].append(L"4.Sair\n");

	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22), HEIGHT / 22, Vec4One);

	m_textsBuffers.push_back(L"Para selecionar uma opção, digite no teclado o número correspondente\n");

	m_textApi->DrawText(
		m_textsBuffers[1].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 40)), HEIGHT / 44, Vec4One);
}

void UIManager::PrintEditorDrawPointMode()
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 2D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);


	m_textsBuffers.push_back(L"Modo desenho de pontos");
	m_textApi->DrawText(
		m_textsBuffers[1].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
}

void UIManager::PrintEditorDrawCircleMode(DrawCircleState _drawCircleState)
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 2D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22, 
		Vec4One);

	switch (_drawCircleState)
	{
	case DrawCircleState::Initial:
		m_textsBuffers.push_back(L"Modo desenho de circulo");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	case DrawCircleState::ChoosingRadius:
		m_textsBuffers.push_back(L"Escolha o raio desejado");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void UIManager::PrintEditorDrawLineMode(DrawLineState _drawLineState)
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 2D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);

	switch (_drawLineState)
	{
	case DrawLineState::Initial:
		m_textsBuffers.push_back(L"Modo desenho de linha");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	case DrawLineState::ChoosingSecondPoint:
		m_textsBuffers.push_back(L"Escolha o segundo ponto");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	default:
		throw std::bad_exception();
		break;
	}


}

void UIManager::PrintEditorDrawRectMode(DrawRectState _drawRectState)
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 2D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);

	switch (_drawRectState)
	{
	case DrawRectState::Initial:
		m_textsBuffers.push_back(L"Modo desenho de retangulo");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	case DrawRectState::ChoosingSecondPoint:
		m_textsBuffers.push_back(L"Escolha o segundo ponto");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	default:
		throw std::bad_exception();
		break;
	}


}

void UIManager::PrintEditorDrawTriangleMode(DrawTriangleState _drawTriangleState)
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 2D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);

	switch (_drawTriangleState)
	{
	case DrawTriangleState::Initial:
		m_textsBuffers.push_back(L"Modo desenho de triangulo");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	case DrawTriangleState::ChoosingSecondPoint:
		m_textsBuffers.push_back(L"Escolha o segundo ponto");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	case DrawTriangleState::ChoosingThirdPoint:
		m_textsBuffers.push_back(L"Escolha o terceiro ponto");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	default:
		throw std::bad_exception();
		break;
	}

}

void UIManager::PrintEditorDrawPolyMode(DrawPolyState _drawPolyState)
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 2D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);

	switch (_drawPolyState)
	{
	case DrawPolyState::Initial:
		m_textsBuffers.push_back(L"Modo desenho de polígono");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	case DrawPolyState::ChoosingSecondPoint:
		m_textsBuffers.push_back(L"Escolha o segundo ponto");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36)), HEIGHT / 44, Vec4One);
		break;
	case DrawPolyState::ChoosingNextPoint:
		m_textsBuffers.push_back(L"Escolha o proximo ponto\n");
		m_textsBuffers[1] = m_textsBuffers[1].append(L"Pressione o botao direito do mouse para fechar o poligono");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
		break;
	default:
		throw std::bad_exception();
		break;
	}

}

void UIManager::PrintEditorSelectColorMode(SelectColorState _selectColorState, int _currentColor)
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 2D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);

	switch (_selectColorState)
	{
	case SelectColorState::Initial:
		m_textsBuffers.push_back(L"Modo selecao de cor\n");
		m_textsBuffers[1] = m_textsBuffers[1].append(L"Selecionando vermelho = " + std::to_wstring(_currentColor));
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
		break;
	case SelectColorState::ChoosingGreen:
		m_textsBuffers.push_back(L"Modo selecao de cor\n");
		m_textsBuffers[1] = m_textsBuffers[1].append(L"Selecionando verde = " + std::to_wstring(_currentColor));
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
		break;
	case SelectColorState::ChoosingBlue:
		m_textsBuffers.push_back(L"Modo selecao de cor\n");
		m_textsBuffers[1] = m_textsBuffers[1].append(L"Selecionando azul = " + std::to_wstring(_currentColor));
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
		break;
	default:
		throw std::bad_exception();
		break;
	}

}

void UIManager::PrintEditorSelectThicknessMode(int _thicknessValue)
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 2D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);

	m_textsBuffers.push_back(L"Modo selecao de espessura\n");
	m_textsBuffers[1] = m_textsBuffers[1].append(L"Espessura selecionada = " + std::to_wstring(_thicknessValue));
	m_textApi->DrawText(
		m_textsBuffers[1].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
}

//-----EDITOR 3D-----//
void UIManager::PrintEditor3DTranslateText()
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 3D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);

	m_textsBuffers.push_back(L"Modo translação\n");
	m_textsBuffers[1] = m_textsBuffers[1].append(L"Selecione o ponto para translação");
	m_textApi->DrawText(
		m_textsBuffers[1].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
}

void UIManager::PrintEditor3DOrbitText(UIPrintComands::OrbitPointState _orbitPointState)
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 3D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);
	switch (_orbitPointState)
	{
	case UIPrintComands::OrbitPointState::Initial:
		m_textsBuffers.push_back(L"Modo Rotacao sobre ponto\n");
		m_textsBuffers[1] = m_textsBuffers[1].append(L"Selecione o ponto para translação");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
		break;
	case UIPrintComands::OrbitPointState::PointSelected:
		m_textsBuffers.push_back(L"Modo Rotacao sobre ponto\n");
		m_textsBuffers[1] = m_textsBuffers[1].append(L"Use as setas do teclado para rotacionar");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void UIManager::PrintEditor3DScaleByPointText(UIPrintComands::ScaleByPointState _scaleByPointState)
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 3D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);
	switch (_scaleByPointState)
	{
	case UIPrintComands::ScaleByPointState::Initial:
		m_textsBuffers.push_back(L"Modo escala sobre ponto\n");
		m_textsBuffers[1] = m_textsBuffers[1].append(L"Selecione o ponto para escala");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
		break;
	case UIPrintComands::ScaleByPointState::PointSelected:
		m_textsBuffers.push_back(L"Modo escala sobre ponto\n");
		m_textsBuffers[1] = m_textsBuffers[1].append(L"Use as setas para escalar");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
		break;
	default:
		throw std::bad_exception();
		break;
	}
}

void UIManager::PrintEditor3DMirrorText(UIPrintComands::MirrorState _mirrorState)
{
	ClearUI();

	m_textsBuffers.push_back(L"Editor 3D\n");
	m_textApi->DrawText(
		m_textsBuffers[0].c_str(),
		Vector2::Vec2D(WIDTH / 2, HEIGHT / 22),
		HEIGHT / 22,
		Vec4One);
	switch (_mirrorState)
	{
	case UIPrintComands::MirrorState::Initial:
		m_textsBuffers.push_back(L"Espelhamento sobre reta\n");
		m_textsBuffers[1] = m_textsBuffers[1].append(L"Selecione o primeiro ponto da reta");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
		break;
	case UIPrintComands::MirrorState::ChoosingSecondPoint:
		m_textsBuffers.push_back(L"Espelhamento sobre reta\n");
		m_textsBuffers[1] = m_textsBuffers[1].append(L"Selecione o segundo ponto da reta");
		m_textApi->DrawText(
			m_textsBuffers[1].c_str(),
			Vector2::Vec2D(WIDTH / 2, HEIGHT - (HEIGHT / 36) - (HEIGHT / 44)), HEIGHT / 44, Vec4One);
		break;
	default:
		throw std::bad_exception();
		break;
	}
}
//-----EDITOR 3D-----//
