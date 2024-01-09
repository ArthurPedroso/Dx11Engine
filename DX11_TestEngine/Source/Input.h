#pragma once

#include "Vectors.h"
#include "Common.h"

enum class INPUT_KEY : unsigned __int64
{
	A = 1LL << 0,
	B = 1LL << 1,
	C = 1LL << 2,
	D = 1LL << 3,
	E = 1LL << 4,
	F = 1LL << 5,
	G = 1LL << 6,
	H = 1LL << 7,
	I = 1LL << 8,
	J = 1LL << 9,
	K = 1LL << 10,
	L = 1LL << 11,
	M = 1LL << 12,
	N = 1LL << 13,
	O = 1LL << 14,
	P = 1LL << 15,
	Q = 1LL << 16,
	R = 1LL << 17,
	S = 1LL << 18,
	T = 1LL << 19,
	U = 1LL << 20,
	V = 1LL << 21,
	W = 1LL << 22,
	X = 1LL << 23,
	Y = 1LL << 24,
	Z = 1LL << 25,
	SPACE = 1LL << 26,
	ENTER = 1LL << 27,
	L_MOUSE_BUTTON = 1LL << 28,
	M_MOUSE_BUTTON = 1LL << 29,
	R_MOUSE_BUTTON = 1LL << 30,
	ESC = 1LL << 31,
	NUM_0 = 1LL << 32,
	NUM_1 = 1LL << 33,
	NUM_2 = 1LL << 34,
	NUM_3 = 1LL << 35,
	NUM_4 = 1LL << 36,
	NUM_5 = 1LL << 37,
	NUM_6 = 1LL << 38,
	NUM_7 = 1LL << 39,
	NUM_8 = 1LL << 40,
	NUM_9 = 1LL << 41,
	SHIFT = 1LL << 42,
	ARROW_LEFT = 1LL << 43,
	ARROW_UP = 1LL << 44,
	ARROW_RIGHT = 1LL << 45,
	ARROW_DOWN = 1LL << 46,
	CTRL = 1LL << 47,
};

class Input
{
friend class Window;

private:
	static Input* m_instance;

	unsigned long long int m_keysDown = 0;
	unsigned long long int m_keysHolded = 0;
	unsigned long long int m_keysUp = 0;
	Vector2::VecInt2D m_mousePos;
	

	void OnKeyPressed(INPUT_KEY _keyPressed);
	void OnKeyReleased(INPUT_KEY _keyPressed);
	void SetMousePos(int _xPos, int _yPos);
	static void FlushKeyStates();
public:
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	
	Input();
	~Input();

	/// <summary>
	/// Retorna true se a tecla foi pressionada
	/// </summary>
	static bool GetKeyDown(INPUT_KEY _key);
	/// <summary>
	/// Retorna true se a tecla esta sendo apertada
	/// </summary>
	static bool GetKey(INPUT_KEY _key);
	/// <summary>
	/// Retorna true se a tecla foi solta
	/// </summary>
	static bool GetKeyUp(INPUT_KEY _key);

	static Vector2::VecInt2D GetMousePos();
	static Vector2::Vec2D GetNormalizedMousePos();
};

