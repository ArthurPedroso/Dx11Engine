#pragma once

#include "CustomWinInclude.h"
#include "Vectors.h"

class IUIText
{
public:
	virtual void DrawText(LPCWSTR _text, Vector2::Vec2D _pos, float _size, Vector4::Vec4D _color) = 0;
	virtual void ClearText() = 0;
};