#pragma once
#include "UIScreen.h"
class UIEngineProfiler : public UIScreen
{
public:
    UIEngineProfiler(std::string name);
    void drawUI() override;

private:
    bool isProfilerOpen = true;
};

