#include "CustomWinInclude.h"
#include <exception>
#pragma once
class BasicExceptions
{
public:
	static void CheckHResult(HRESULT _result) { if (_result != 0) throw std::bad_exception(); }
};

