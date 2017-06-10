#pragma once

#include "ofMain.h"

namespace ScreenGuide{
    
    const static float renderW = 3840;
    const static float renderH = 1080;
    const static float centerX = renderW/2;
    const static float centerY = renderH/2;
    
    const static float marginH = 300;
    const static float marginW = 300;
    
    const static ofRectangle safeAreaL(550, 270, 1030, 640);
    const static ofRectangle safeAreaR(2590, 270, 680, 640);
  
    void drawGuide();
};
