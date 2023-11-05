#include "UIToolbar.h"
#include "GameObjectManager.h"

UIToolbar::UIToolbar(std::string name) : UIScreen(name)
{

}

void UIToolbar::drawUI()
{
    ImGui::BeginMainMenuBar();


    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("New"))
        {

        }
        if (ImGui::MenuItem("Save"))
        {

        }
        if (ImGui::MenuItem("Open"))
        {

        }
        if (ImGui::MenuItem("Exit"))
        {

        }
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Game Object")) {

        if (ImGui::MenuItem("Create Cube"))
        {
            GameObjectManager::getInstance()->createGameObject(GameObjectManager::CUBE);
        }

        if (ImGui::MenuItem("Create Sphere"))
        {

        }

        if (ImGui::MenuItem("Create Plane")) 
        {
            GameObjectManager::getInstance()->createGameObject(GameObjectManager::PLANE);
        }
        if (ImGui::BeginMenu("Create Light")) 
        {
            if (ImGui::MenuItem("Point Light")) 
            {

            }
            ImGui::EndMenu();
        }

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}
