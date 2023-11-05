#pragma once
#include "UIScreen.h"
#include "GameObjectManager.h"
#include "GameObject.h"
class UIinspectorWindow : public UIScreen
{
public:
	UIinspectorWindow(std::string name);
	~UIinspectorWindow();

	void drawUI() override;

private:

	GameObject* selectedGameObject = nullptr;

	float m_rot_x;
	float m_rot_y;
	float m_rot_z;

	float m_pos_x;
	float m_pos_y;
	float m_pos_z;

	float m_scale_x;
	float m_scale_y;
	float m_scale_z;





};

