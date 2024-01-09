#include "Window.h"
#include "WindowsMsgMap.h"
#include <sstream>

Window::WindowClass Window::WindowClass::s_windowClass; //inicia o singleton

//-----NESTED WindowClass-----//
const LPCWSTR Window::WindowClass::GetName()
{
    return sk_className;
}
HINSTANCE Window::WindowClass::GetInstance()
{
    return s_windowClass.m_hInstance;
}
Window::WindowClass::WindowClass()
{

	m_hInstance = GetModuleHandle(nullptr);

	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_OWNDC;
	windowClass.lpfnWndProc = HandleMsgSetup; //callback
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = nullptr;
	windowClass.hCursor = nullptr;
	windowClass.hbrBackground = nullptr;
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = GetName();
	windowClass.hIconSm = nullptr;


	// registrar a class desssa window
	RegisterClassEx(&windowClass);
}
Window::WindowClass::~WindowClass()
{
	UnregisterClass(sk_className, GetInstance());
}
//-----NESTED WindowClass-----//


//-----MAIN CLASS-----//
/// <summary>
/// Func de instalacao.
/// Essa func apenas registra as funcoes procedimento, 
/// e comeca a redirecionar as chamadas de funcoes estaticas para o metodo HandleMsg.
/// </summary>
LRESULT CALLBACK Window::HandleMsgSetup(HWND _windowsHandler, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (_msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(_lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams); //recupera ponteiro passado como parametro no construtor
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(_windowsHandler, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(_windowsHandler, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// forward message to window instance handler
		return pWnd->HandleMsg(_windowsHandler, _msg, _wParam, _lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(_windowsHandler, _msg, _wParam, _lParam);
}
/// <summary>
/// Func adaptador.
/// Essa func redireciona as chamadas de funcoes estaticas mara o metodo HandleMsg.
/// </summary>
LRESULT CALLBACK Window::HandleMsgThunk(HWND _windowsHandler, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	// retrieve ptr to window instance
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(_windowsHandler, GWLP_USERDATA));
	// forward message to window instance handler
	return pWnd->HandleMsg(_windowsHandler, _msg, _wParam, _lParam);
}
LRESULT Window::HandleMsg(HWND _windowsHandler, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	static WindowsMsgMap msgMap;
	unsigned char formatedParam;
	//OutputDebugStringA(msgMap(_msg, _lParam, _wParam).c_str());


	switch (_msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0; //retorna 0 pq a destruicao da janela eh responsabilidade do destrutor da classe
	case WM_KEYDOWN:
		formatedParam = _wParam;
		if (formatedParam >= 65 && formatedParam <= 90)
			m_input.OnKeyPressed((INPUT_KEY)(1LL << (formatedParam - 65)));
		else if (formatedParam >= 48 && formatedParam <= 57)
			m_input.OnKeyPressed((INPUT_KEY)(1LL << (formatedParam - 16)));
		else if (formatedParam >= 37 && formatedParam <= 41)
			m_input.OnKeyPressed((INPUT_KEY)(1LL << (formatedParam + 6)));
		else if(formatedParam == 32)
			m_input.OnKeyPressed(INPUT_KEY::SPACE);
		else if(formatedParam == VK_RETURN)
			m_input.OnKeyPressed(INPUT_KEY::ENTER);
		else if (formatedParam == 27)
			m_input.OnKeyPressed(INPUT_KEY::ESC);
		else if (formatedParam == VK_SHIFT)
			m_input.OnKeyPressed(INPUT_KEY::SHIFT);
		else if (formatedParam == VK_CONTROL)
			m_input.OnKeyPressed(INPUT_KEY::CTRL);
			//codigo de tecla eh igual a codigo ASCII
		//	OutputDebugStringA("Apertou F!");
		break;
	case WM_KEYUP:
		formatedParam = _wParam;
		if (formatedParam >= 65 && formatedParam <= 90)
			m_input.OnKeyReleased((INPUT_KEY)(1LL << (formatedParam - 65)));
		else if(formatedParam >= 48 && formatedParam <= 57)
			m_input.OnKeyReleased((INPUT_KEY)(1LL << (formatedParam - 16)));
		else if(formatedParam >= 37 && formatedParam <= 41)
			m_input.OnKeyReleased((INPUT_KEY)(1LL << (formatedParam + 6)));
		else if (formatedParam == 32)
			m_input.OnKeyReleased(INPUT_KEY::SPACE);
		else if (formatedParam == VK_RETURN)
			m_input.OnKeyReleased(INPUT_KEY::ENTER);
		else if (formatedParam == 27)
			m_input.OnKeyReleased(INPUT_KEY::ESC);
		else if (formatedParam == VK_SHIFT)
			m_input.OnKeyReleased(INPUT_KEY::SHIFT);
		else if (formatedParam == VK_CONTROL)
			m_input.OnKeyReleased(INPUT_KEY::CTRL);

		//if (_wParam == 'F') //codigo de tecla eh igual a codigo ASCII
		//	OutputDebugStringA("Apertou F!");
		break;
	case WM_CHAR: //Input de digitacao de texto
		break;
	case WM_LBUTTONDOWN: //CLick esquerdo do mouse, retorna coordenadas do mouse(relativo a janela)
		m_input.OnKeyPressed(INPUT_KEY::L_MOUSE_BUTTON);
		break;
	case WM_LBUTTONUP:
		m_input.OnKeyReleased(INPUT_KEY::L_MOUSE_BUTTON);
		break;
	case WM_MBUTTONDOWN:
		m_input.OnKeyPressed(INPUT_KEY::M_MOUSE_BUTTON);
		break;
	case WM_MBUTTONUP:
		m_input.OnKeyReleased(INPUT_KEY::M_MOUSE_BUTTON);
		break;
	case WM_RBUTTONDOWN:
		m_input.OnKeyPressed(INPUT_KEY::R_MOUSE_BUTTON);
		break;
	case WM_RBUTTONUP:
		m_input.OnKeyReleased(INPUT_KEY::R_MOUSE_BUTTON);
		break;
	case WM_MOUSEMOVE:
		const POINTS point = MAKEPOINTS(_lParam);

		m_input.SetMousePos(point.x, point.y);
		break; 
	}

	m_windowMinimized = IsIconic(_windowsHandler);
	return DefWindowProc(_windowsHandler, _msg, _wParam, _lParam);
}
Window::Window(int _pxlWidth, int _pxlHeight, LPCWSTR _name) : m_input(), m_windowMinimized(false)
{
	m_pxlWidth = _pxlWidth;
	m_pxlHeight = _pxlHeight;

	// calculate window size based on desired client region size
	RECT windowRect;
	windowRect.left = 100;
	windowRect.right = _pxlWidth + windowRect.left;
	windowRect.top = 100;
	windowRect.bottom = _pxlHeight + windowRect.top;
	if (AdjustWindowRect(&windowRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw std::bad_exception();
	}
	// cria uma instancia da window
	m_windowHandler = CreateWindow(
		WindowClass::GetName(),
		_name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		800, 400, // posicao inicial
		windowRect.right - windowRect.left, // resolucao da janela
		windowRect.bottom - windowRect.top, // resolucao da janela
		nullptr,
		nullptr,
		WindowClass::GetInstance(),
		this
	);

	ShowWindow(m_windowHandler, SW_SHOW);

	//tem que ser instanciado DEPOIS do window handler
	m_graphics = std::make_unique<GraphicsManager>(m_windowHandler);
}
Window::~Window()
{
	DestroyWindow(m_windowHandler);
}
GraphicsManager& Window::GetGraphics()
{
	return *m_graphics;
}
bool Window::WindowMinimized()
{
	return m_windowMinimized;
}
/// <summary>
/// Despacha a queue de msgs e retorna codigo de quit se necessario
/// </summary>
/// <param name="_returnCode">Codigo da msg quando quit ocorre</param>
/// <returns>True se quit for detectado, se não, retorna falso</returns>
bool Window::ComputeMessages(int& _outReturnCode)
{
	MSG windowMsg;

	Input::FlushKeyStates();
	//vai dando dispatch na queue ate encontrar quit, ou esvaziar
	while (PeekMessage(&windowMsg, nullptr, 0, 0, PM_REMOVE))
	{
		if (windowMsg.message == WM_QUIT)
		{
			//se detectar message quit, retorna o codigo
			_outReturnCode = windowMsg.wParam;
			return true;
		}

		TranslateMessage(&windowMsg);
		DispatchMessage(&windowMsg);
	}

	//Se a fila de msgs estiver vazia, retorna como false
	return false;
}
//-----MAIN CLASS-----//
