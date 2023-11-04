#pragma once
#include "GameObject.h"
#include "GameObjectManager.h"
#include "UIScreen.h"


class UISceneOutliner : public UIScreen
{
public:
	UISceneOutliner(std::string name);
	~UISceneOutliner();

	void drawUI() override;

private:
	std::vector<GameObject*> ObjectList;
	bool isSceneOutlinerOpen = true;
};

