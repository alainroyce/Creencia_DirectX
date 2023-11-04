#include "UIinspectorWindow.h"

UIinspectorWindow::UIinspectorWindow(std::string name) : UIScreen(name)
{
}

void UIinspectorWindow::drawUI()
{
    ImGuiWindowFlags windowFlags = 0;

    ImGui::Begin("Inspector", NULL, windowFlags);
    ImGui::SetWindowSize(ImVec2(200, 500));
  

    ImGui::End();
}

