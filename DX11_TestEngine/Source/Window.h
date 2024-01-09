#pragma once

#include "CustomWinInclude.h"
#include "GraphicsManager.h"
#include "Input.h"
#include <memory>

/// <summary>
/// Essa Classe encapsula os comandos de criacao e registro de uma janela do windows
/// </summary>
class Window
{
private:
// Types:
	/// <summary>
	/// singleton que gertencia registro/limpeza da da Window Class	
	/// </summary>
	class WindowClass
	{
	private:
	//Fields:
		HINSTANCE m_hInstance;

		static constexpr const LPCWSTR sk_className = L"dx11Tests";
		static WindowClass s_windowClass;
	// Methods:
		WindowClass(const WindowClass&) = delete; //deletea esse construtor
		WindowClass& operator=(const WindowClass&) = delete; //deleta esse operador
		WindowClass();
		~WindowClass();

	public:
	// Methods:
		static const LPCWSTR GetName();
		static HINSTANCE GetInstance();
	};

// Fields:
	std::unique_ptr<GraphicsManager> m_graphics;
	HWND m_windowHandler;
	Input m_input;
	int m_pxlWidth;
	int m_pxlHeight;
	bool m_windowMinimized;
// Methods:
	LRESULT HandleMsg(HWND _windowsHandler, UINT _msg, WPARAM _wParam, LPARAM _lParam);

	static LRESULT CALLBACK HandleMsgSetup(HWND _windowsHandler, UINT _msg, WPARAM _wParam, LPARAM _lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND _windowsHandler, UINT _msg, WPARAM _wParam, LPARAM _lParam);

public:
// Methods:
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(int _pxlWidth, int _pxlHeight, LPCWSTR _name);
	~Window();

	GraphicsManager& GetGraphics();
	bool WindowMinimized();

	static bool ComputeMessages(int& _outReturnCode);
};

