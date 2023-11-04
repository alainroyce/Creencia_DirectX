#pragma once
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <string>
#include "UIManager.h"



class UIScreen
{
protected:
    std::string name;

    UIScreen(std::string name);
    ~UIScreen();

    std::string getName();
    virtual void drawUI() = 0;

    friend class UIManager;

};


