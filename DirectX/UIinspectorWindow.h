#pragma once
#include "UIScreen.h"
class UIinspectorWindow : public UIScreen
{
public:
	UIinspectorWindow(std::string name);
	~UIinspectorWindow();

	void drawUI() override;
};

