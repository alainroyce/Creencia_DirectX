#include "UIEngineProfiler.h"

UIEngineProfiler::UIEngineProfiler(std::string name) : UIScreen(name)
{
}

void UIEngineProfiler::drawUI()
{

    ImGuiWindowFlags windowFlags = 0;

    ImGui::Begin("Engine Profiler", NULL, windowFlags);
    ImGui::SetWindowSize(ImVec2(500, 100));
       
    ImGuiIO& io = ImGui::GetIO();
        
    float avgFrameTimeMs = io.Framerate / 1000.0f;   
    int frameRate = static_cast<int>(io.Framerate);

       
    std::string ms_text = "Average MS per frame: " + std::to_string(avgFrameTimeMs) + "ms | Framerate: " + std::to_string(frameRate) + " fps ";
    ImGui::Text(ms_text.c_str());  
    ImGui::End();
    
}
