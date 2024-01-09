#include "Input.h"
#include "Window.h"
#include <exception>

Input* Input::m_instance = nullptr;

Input::Input()
{
	if (m_instance != nullptr)
		throw std::bad_exception();
	else
		m_instance = this;
}

Input::~Input()
{
	m_instance = nullptr;
}

void Input::SetMousePos(int _xPos, int _yPos)
{
	m_mousePos.x = _xPos;
	m_mousePos.y = _yPos;
}
void Input::OnKeyPressed(INPUT_KEY _keyPressed)
{
	if((m_keysHolded & (unsigned __int64)_keyPressed) == 0)
	{
		m_keysDown += (unsigned __int64)_keyPressed;
	}
}
void Input::OnKeyReleased(INPUT_KEY _keyReleased)
{
	m_keysUp += (unsigned __int64)_keyReleased;
}
void Input::FlushKeyStates()
{
	if (m_instance == nullptr) return;
	m_instance->m_keysHolded |= m_instance->m_keysDown;
	m_instance->m_keysHolded -= m_instance->m_keysUp;

	m_instance->m_keysDown = 0;
	m_instance->m_keysUp = 0;
}

/// <summary>
/// Retorna true se a tecla foi pressionada
/// </summary>
bool Input::GetKeyDown(INPUT_KEY _key)
{
	if (m_instance == nullptr) return false;
	return ((unsigned __int64)_key & m_instance->m_keysDown);
}
/// <summary>
/// Retorna true se a tecla esta sendo apertada
/// </summary>
bool Input::GetKey(INPUT_KEY _key)
{
	if (m_instance == nullptr) return false;
	return (((unsigned __int64)_key & m_instance->m_keysHolded));
}
/// <summary>
/// Retorna true se a tecla foi solta
/// </summary>
bool Input::GetKeyUp(INPUT_KEY _key)
{
	if (m_instance == nullptr) return false;
	return ((unsigned __int64)_key & m_instance->m_keysUp);
}

Vector2::VecInt2D Input::GetMousePos()
{
	if (m_instance == nullptr) return Vector2::VecInt2Zero;

	return m_instance->m_mousePos;
}

Vector2::Vec2D Input::GetNormalizedMousePos()
{
	if (m_instance == nullptr) return Vector2::VecInt2Zero;
	Vector2::Vec2D mousePos = (Vector2::Vec2D(m_instance->m_mousePos.x / (float)WIDTH, m_instance->m_mousePos.y / (float)HEIGHT) + Vector2::Vec2D(-0.5f, -0.5f)) * 2.0f;
	mousePos.y *= -1.0f;
	return mousePos;
}
