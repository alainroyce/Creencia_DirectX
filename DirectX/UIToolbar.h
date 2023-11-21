#pragma once
#include "UIScreen.h"


class UIToolbar : public UIScreen
{
public:
	UIToolbar(std::string name);
	void drawUI() override;

	
};

