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
    
    for (const auto& object : this->ObjectList)
    {
        if (ImGui::Button(object->GetName().c_str()))
        {
            GameObjectManager::getInstance()->setSelectGameObject(object);
        }
    }


    ImGui::End();
}
