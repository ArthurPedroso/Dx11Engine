#pragma once

#include "ControllerStateBase.h"

class MainMenuControllerState : public ControllerStateBase
{
public:
	virtual void Update() override;
	virtual void OnStateEnter() override;
	virtual void OnStateExit() override;

	//Especifica que queremos usar o construtor da classe pai
	using ControllerStateBase::ControllerStateBase;
};

