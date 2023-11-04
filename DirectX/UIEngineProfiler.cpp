#include "UIEngineProfiler.h"

UIEngineProfiler::UIEngineProfiler(std::string name) : UIScreen(name)
{
}

void UIEngineProfiler::drawUI()
{

    if (ImGui::Begin("Profiler", &isProfilerOpen))
    {
        std::string ms_text = "Application Average " + std::to_string(ImGui::GetIO().Framerate / 1000.0f) + " ms/frame (" + std::to_string(ImGui::GetIO().Framerate) + " FPS)";
        ImGui::Text(ms_text.c_str());

        ImGui::End();
    }
}
