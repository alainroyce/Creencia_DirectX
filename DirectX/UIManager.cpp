#include "UIManager.h"
#include "UIToolbar.h"
#include "UISceneOutliner.h"
#include "UIEngineProfiler.h"
#include "UIinspectorWindow.h"



UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::getInstance()
{
    return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
    sharedInstance = new UIManager();

    //IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(windowHandle);
    ImGui_ImplDX11_Init(GraphicsEngine::get()->getDevice(), GraphicsEngine::get()->getD3D11DeviceContext());
  
    UIToolbar* toolbar = new UIToolbar("Toolbar");
    sharedInstance->UIList.push_back(toolbar);

    UIEngineProfiler* profiler = new UIEngineProfiler("Profiler");
   sharedInstance->UIList.push_back(profiler);

   UISceneOutliner* outliner = new UISceneOutliner("Outliner");
   sharedInstance->UIList.push_back(outliner);

   UIinspectorWindow* inspector = new UIinspectorWindow("Inspector");
   sharedInstance->UIList.push_back(inspector);
}

void UIManager::destroy()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    delete sharedInstance;
}

void UIManager::drawUI()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < UIList.size(); i++)
    {
        this->UIList[i]->drawUI();
    }
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}



UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}


