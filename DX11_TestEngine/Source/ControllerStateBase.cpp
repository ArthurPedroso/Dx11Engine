
#include "ControllerStateBase.h"

ControllerStateBase::ControllerStateBase(IAppController* _appController) : m_appController(_appController), 
																			m_uiManager(_appController->GetUIManager()),
																			m_drawSystem(_appController->GetDrawSystem()),
																			m_jsonIO(_appController->GetJsonIO())
{
}
