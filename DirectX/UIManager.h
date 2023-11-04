#pragma once
#include "GraphicsEngine.h"
#include <vector>
#include <unordered_map>
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "Windows.h"
#include"UIScreen.h"

class UIScreen;

using namespace std;
class UIManager
{
public:
    static UIManager* getInstance();
    static void initialize(HWND windowHandle);
    static void destroy();

    void drawUI();

private:

    UIManager();
    ~UIManager();

 
    UIManager(UIManager const&) {};
    UIManager& operator=(UIManager const&) {};
    static UIManager* sharedInstance;
    
    vector<UIScreen*> UIList;
};

