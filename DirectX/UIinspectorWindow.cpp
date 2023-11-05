#include "UIinspectorWindow.h"

UIinspectorWindow::UIinspectorWindow(std::string name) : UIScreen(name)
{
}

void UIinspectorWindow::drawUI()
{
    ImGuiWindowFlags windowFlags = 0;

    ImGui::Begin("Inspector", NULL, windowFlags);
    ImGui::SetWindowSize(ImVec2(200, 300));

    this->selectedGameObject = GameObjectManager::getInstance()->getSelectedGameObject();

    if (selectedGameObject == nullptr)
    {
        ImGui::End();
        return;
    }
    else
    {
        std::string nameString = "Selected Object Name: " + selectedGameObject->GetName();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), nameString.c_str());
        ImGui::Text("\n");

        m_pos_x = this->selectedGameObject->GetLocalPosition().m_x;
        m_pos_y = this->selectedGameObject->GetLocalPosition().m_y;
        m_pos_z = this->selectedGameObject->GetLocalPosition().m_z;

        m_scale_x = this->selectedGameObject->GetLocalScale().m_x;
        m_scale_y = this->selectedGameObject->GetLocalScale().m_y;
        m_scale_z = this->selectedGameObject->GetLocalScale().m_z;

        m_rot_x = this->selectedGameObject->GetLocalRotation().m_x;
        m_rot_y = this->selectedGameObject->GetLocalRotation().m_y;
        m_rot_z = this->selectedGameObject->GetLocalRotation().m_z;


        float rotation[3] = { m_rot_x, m_rot_y, m_rot_z };
        float position[3] = { m_pos_x, m_pos_y, m_pos_z };
        float scale[3] = { m_scale_x, m_scale_y, m_scale_z };

        ImGui::DragFloat3("Position", position, 1);
        ImGui::DragFloat3("Rotation", rotation, 1);
        ImGui::DragFloat3("Scale", scale, 1);


        
        this->selectedGameObject->SetPosition(position[0], position[1], position[2]);

        if (this->selectedGameObject->GetName() == "Plane") // y axis cannot be scaled
        {
            this->selectedGameObject->SetScale(scale[0], m_scale_y, scale[2]);
        }
        else if(this->selectedGameObject->GetName() == "Cube")
        {
            this->selectedGameObject->SetScale(scale[0], scale[1], scale[2]);
        }
        this->selectedGameObject->SetRotation(rotation[0], rotation[1], rotation[2]);

    }
    
    ImGui::End();
}

