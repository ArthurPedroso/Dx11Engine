#pragma once

#include "ControllerStateBase.h"

class Editor3DControllerState : public ControllerStateBase
{
private:
	enum class Editor3DState : int
	{
		Translate = 0,
		OrbitPoint = 1,
		ScaleByPoint = 2,
		Mirror = 3,
		Count = 4
	};

	Vec2D m_auxPosition;
	Editor3DState m_editorState;
	std::shared_ptr<GraphicElement> m_selectedElement;
	UIPrintComands::MirrorState m_mirrorState;
	UIPrintComands::OrbitPointState m_orbitPointState;
	UIPrintComands::ScaleByPointState m_scaleByPointState;

	float m_rotation;



	void ChangeEditorState(Editor3DState _newState);

	void OnLeftMouseClick();
	void OnIncreaseValue();
	void OnDecreaseValue();
	void OnSelect();
	void OnNoneSelected();
public:
	virtual void Update() override;
	virtual void OnStateEnter() override;
	virtual void OnStateExit() override;


	//Especifica que queremos usar o construtor da classe pai
	using ControllerStateBase::ControllerStateBase;
};

