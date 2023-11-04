#include "UISceneOutliner.h"

UISceneOutliner::UISceneOutliner(std::string name) : UIScreen(name)
{
}


void UISceneOutliner::drawUI()
{
    this->ObjectList = GameObjectManager::getInstance()->getAllGameObject();
    
    ImGuiWindowFlags windowFlags = 0;
    ImGui::Begin("Scene Outliner", NULL, windowFlags);
    ImGui::SetWindowSize(ImVec2(210, 500));
    
    for (int i = 0; i < this->ObjectList.size(); i++)
    {
        if (ImGui::Button(this->ObjectList[i]->GetName().c_str())) {
            GameObjectManager::getInstance()->setSelectGameObject(this->ObjectList[i]);
        }
    }


    ImGui::End();
}
